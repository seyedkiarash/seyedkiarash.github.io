#!/usr/bin/env python3
import pathlib, re
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon, Rectangle, Circle
from vcdvcd import VCDVCD

ROOT = pathlib.Path(__file__).resolve().parent.parent
OUT = ROOT / "reports" / "figures"
OUT.mkdir(parents=True, exist_ok=True)

plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 8,
                     "axes.linewidth": 0.6, "pdf.fonttype": 42})
INK, ON, OFF, PANEL = "#1c1f23", "#e5402b", "#efe9e6", "#fbfaf7"
BLUE = "#1f4e79"

SEG_HEX = {0: "1111110", 1: "0110000", 2: "1101101", 3: "1111001", 4: "0110011",
           5: "1011011", 6: "1011111", 7: "1110000", 8: "1111111", 9: "1111011",
           10: "1110111", 11: "0011111", 12: "1001110", 13: "0111101", 14: "1001111", 15: "1000111"}


def seg_of_char(ch):
    if ch == " ":
        return "0000000"
    return SEG_HEX[int(ch, 16)]


def _segment_polys(x0, y0, w=1.0, h=1.8, t=0.16):
    def hseg(cx, cy):
        L = w - 2 * t
        return [(cx - L/2, cy), (cx - L/2 + t/2, cy + t/2), (cx + L/2 - t/2, cy + t/2),
                (cx + L/2, cy), (cx + L/2 - t/2, cy - t/2), (cx - L/2 + t/2, cy - t/2)]
    def vseg(cx, cy):
        L = h/2 - 2 * t
        return [(cx, cy - L/2), (cx + t/2, cy - L/2 + t/2), (cx + t/2, cy + L/2 - t/2),
                (cx, cy + L/2), (cx - t/2, cy + L/2 - t/2), (cx - t/2, cy - L/2 + t/2)]
    sk = 0.12
    def slant(poly):
        return [(x + sk * (y - y0) / h, y) for x, y in poly]
    cx = x0 + w / 2
    polys = {
        "a": hseg(cx, y0 + h - t/2), "g": hseg(cx, y0 + h/2), "d": hseg(cx, y0 + t/2),
        "f": vseg(x0 + t/2, y0 + 3*h/4), "b": vseg(x0 + w - t/2, y0 + 3*h/4),
        "e": vseg(x0 + t/2, y0 + h/4), "c": vseg(x0 + w - t/2, y0 + h/4),
    }
    return {k: slant(v) for k, v in polys.items()}


def draw_display(ax, digits, x=0.0, y=0.0, label=None, active=None):
    pad = 0.35
    ax.add_patch(Rectangle((x - pad, y - pad), 4 * 1.45 - 0.45 + 2 * pad, 1.8 + 2 * pad,
                           facecolor="#26282b", edgecolor="none", zorder=0))
    for i, pattern in enumerate(digits):
        polys = _segment_polys(x + i * 1.45, y)
        for k, name in enumerate("abcdefg"):
            lit = pattern[k] == "1"
            ax.add_patch(Polygon(polys[name], closed=True, facecolor=ON if lit else "#3a3c40",
                                 edgecolor="none", zorder=1))
        if active is not None and active == i:
            ax.add_patch(Circle((x + i * 1.45 + 0.5, y - pad - 0.18), 0.07, color=BLUE, zorder=2))
    if label:
        ax.text(x + 2.7, y - pad - (0.5 if active is not None else 0.32), label,
                ha="center", va="top", fontsize=7.5, color=INK)


def frames_figure(name, frames, labels, cols=3, title=None):
    rows = (len(frames) + cols - 1) // cols
    fig, ax = plt.subplots(figsize=(1.95 * cols, 1.05 * rows + (0.25 if title else 0)))
    for i, (fr, lb) in enumerate(zip(frames, labels)):
        r, c = divmod(i, cols)
        draw_display(ax, fr, x=c * 7.2, y=-r * 3.3, label=lb)
    ax.set_xlim(-0.6, cols * 7.2 - 1.0)
    ax.set_ylim(-(rows - 1) * 3.3 - 1.0, 2.3)
    ax.set_aspect("equal"); ax.axis("off")
    if title:
        ax.set_title(title, fontsize=8.5, color=INK, pad=4)
    fig.savefig(OUT / f"{name}.pdf", bbox_inches="tight", pad_inches=0.03)
    plt.close(fig)


def text_frames(texts):
    return [[seg_of_char(ch) for ch in t] for t in texts]


def _val(tv, t):
    v = tv[0][1]
    for ti, vi in tv:
        if ti > t:
            break
        v = vi
    return v


def waveform(name, vcd_path, signals, t0, t1, height=None, fmt=None, title=None, time_unit=("ns", None)):
    vcd = VCDVCD(str(vcd_path), store_tvs=True)
    fmt = fmt or {}
    unit, scale = time_unit
    unit_s = {"ns": 1e-9, "µs": 1e-6, "ms": 1e-3}[unit]
    tick = float(vcd.timescale["timescale"])
    t0, t1 = int(t0 * unit_s / tick), int(t1 * unit_s / tick)
    scale = tick / unit_s
    n = len(signals)
    fig, ax = plt.subplots(figsize=(6.3, height or 0.38 * n + 0.45))
    for row, (label, sig, kind) in enumerate(signals):
        tv = [(t, v) for t, v in vcd[sig].tv]
        y = n - 1 - row
        ax.text(t0 * scale - (t1 - t0) * scale * 0.012, y + 0.35, label, ha="right", va="center", fontsize=7.5, color=INK)
        pts = sorted(set([t0] + [t for t, _ in tv if t0 < t < t1] + [t1]))
        if kind == "bit":
            xs, ys = [], []
            for a in pts:
                v = _val(tv, a)
                lv = 0.7 if v == "1" else (0.0 if v == "0" else 0.35)
                xs.append(a * scale); ys.append(y + lv)
            X, Y = [], []
            for i in range(len(xs)):
                if i:
                    X.append(xs[i]); Y.append(ys[i - 1])
                X.append(xs[i]); Y.append(ys[i])
            ax.plot(X, Y, color=BLUE, lw=0.9)
        else:
            for i in range(len(pts) - 1):
                a, b = pts[i], pts[i + 1]
                v = _val(tv, a)
                xa, xb = a * scale, b * scale
                d = min((xb - xa) * 0.25, (t1 - t0) * scale * 0.006)
                ax.fill([xa, xa + d, xb - d, xb, xb - d, xa + d], [y + 0.35, y + 0.7, y + 0.7, y + 0.35, y, y],
                        facecolor="#e8eef5", edgecolor=BLUE, lw=0.7)
                txt = fmt.get(label, lambda s: hex(int(s, 2))[2:].upper() if set(s) <= {"0", "1"} else "x")(v)
                if (xb - xa) > (t1 - t0) * scale * 0.035:
                    ax.text((xa + xb) / 2, y + 0.35, txt, ha="center", va="center", fontsize=6.8, color=INK)
    ax.set_xlim(t0 * scale, t1 * scale)
    ax.set_ylim(-0.3, n)
    ax.set_yticks([])
    for s in ("left", "right", "top"):
        ax.spines[s].set_visible(False)
    ax.set_xlabel(f"time ({unit})", fontsize=7.5)
    ax.tick_params(axis="x", labelsize=7)
    ax.grid(axis="x", color="#dddddd", lw=0.4)
    if title:
        ax.set_title(title, fontsize=8.5, color=INK, loc="left")
    fig.savefig(OUT / f"{name}.pdf", bbox_inches="tight", pad_inches=0.03)
    plt.close(fig)


def seg_text(bits):
    if not set(bits) <= {"0", "1"} or len(bits) != 7:
        return "x"
    pos = "".join("1" if c == "0" else "0" for c in bits)
    for k, v in SEG_HEX.items():
        if v == pos:
            return "%X" % k
    return "?"


def sim(path):
    return ROOT / path


def lab07():
    L = "lab07-seven-segment"
    frames_figure("lab07_part1", text_frames(["0000", "3333", "AAAA", "FFFF"]),
                  ["DIP[3:0] = 0000", "DIP[3:0] = 0011", "DIP[3:0] = 1010", "DIP[3:0] = 1111"], cols=4)
    one = [["0000000"] * 4 for _ in range(4)]
    for i, d in enumerate("1234"):
        one[i][i] = seg_of_char(d)
    fig, ax = plt.subplots(figsize=(7.8, 1.25))
    for i in range(4):
        draw_display(ax, one[i], x=i * 7.6, y=0, label=f"dig = {format(8 >> i, '04b')}", active=i)
    draw_display(ax, text_frames(["1234"])[0], x=4 * 7.6 + 1.2, y=0, label="what the eye sees")
    ax.annotate("", xy=(4 * 7.6 + 0.75, 0.9), xytext=(4 * 7.6 - 1.2, 0.9), arrowprops=dict(arrowstyle="->", color=INK, lw=0.8))
    ax.set_xlim(-0.6, 5 * 7.6 + 0.8); ax.set_ylim(-1.1, 2.3); ax.set_aspect("equal"); ax.axis("off")
    fig.savefig(OUT / "lab07_part3_frames.pdf", bbox_inches="tight", pad_inches=0.03); plt.close(fig)

    waveform("lab07_part3_wave", sim(f"{L}/part3-multiplexing/sim/tb_display_1234.vcd"),
             [("clk", "tb_display_1234.clk", "bit"), ("scan_clk", "tb_display_1234.dut.scan_clk", "bit"),
              ("state", "tb_display_1234.dut.state[1:0]", "bus"), ("dig[3:0]", "tb_display_1234.dig[3:0]", "bus"),
              ("number", "tb_display_1234.dut.number[3:0]", "bus")],
             100, 900, fmt={"dig[3:0]": lambda s: s if len(s) == 4 else s.zfill(4)},
             title="Part 3 simulation (scan divider shortened to 2 cycles)")

    s = "403101383"
    wins = [(s + s)[i:i + 4] for i in range(9)]
    frames_figure("lab07_part5", text_frames(wins), [f"window {i}  (t = {2*i} s)" for i in range(9)], cols=3)

    frames_figure("lab07_part6", text_frames(["0000", "0009", "0010", "0599", "1000", "9599"]),
                  ["0.0 s", "0.9 s", "1.0 s", "59.9 s", "1 min 00.0 s", "9 min 59.9 s"], cols=3)
    waveform("lab07_part6_wave", sim(f"{L}/part6-stopwatch/sim/tb_stopwatch.vcd"),
             [("tick_clk", "tb_stopwatch.dut.tick_clk", "bit"),
              ("c1: tenths", "tb_stopwatch.dut.n1[3:0]", "bus"), ("e2 (c1 done)", "tb_stopwatch.dut.e2", "bit"),
              ("c2: seconds", "tb_stopwatch.dut.n2[3:0]", "bus"), ("e3 (c2 done)", "tb_stopwatch.dut.e3", "bit"),
              ("c3: 10 s", "tb_stopwatch.dut.n3[3:0]", "bus")],
             0, 72, title="Part 6: cascaded counters (tick shortened to 32 clock cycles)", time_unit=("µs", None))

    log = (ROOT / L / "bonus-c-snake/sim/tb_snake_display.log").read_text()
    frames, labels = [], []
    for m in re.finditer(r"FRAME head=(\d+) d3=(\d+) d2=(\d+) d1=(\d+) d0=(\d+)", log):
        frames.append([m.group(2), m.group(3), m.group(4), m.group(5)])
        labels.append(f"head at position {m.group(1)}")
    frames_figure("lab07_snake", frames, labels, cols=4)


def led_row(ax, bits, x, y, label=None):
    for i, b in enumerate(bits):
        ax.add_patch(Circle((x + i * 0.9, y), 0.32, facecolor=ON if b == "1" else OFF,
                            edgecolor="#b9b2ad", lw=0.6))
    if label:
        ax.text(x - 0.7, y, label, ha="right", va="center", fontsize=7.2, color=INK)


def lab06():
    L = "lab06-sequential-zynq"
    pats = ["10000", "11000", "11100", "11110", "11111", "01111", "00111", "00011", "00001", "00000"]
    fig, ax = plt.subplots(figsize=(2.6, 3.0))
    for i, p in enumerate(pats):
        led_row(ax, p, 0, -i, label=f"state {i}")
    ax.text(1.8, 0.75, "LED[4] ... LED[0]", ha="center", fontsize=7, color=INK)
    ax.set_xlim(-2.4, 4.2); ax.set_ylim(-9.6, 1.1); ax.set_aspect("equal"); ax.axis("off")
    fig.savefig(OUT / "lab06_ledflow.pdf", bbox_inches="tight", pad_inches=0.03); plt.close(fig)

    waveform("lab06_minigame_wave", sim(f"{L}/part3-reaction-game/sim/tb_mini_game.vcd"),
             [("clk (game)", "tb_mini_game.clk", "bit"), ("button[3:0]", "tb_mini_game.button[3:0]", "bus"),
              ("state", "tb_mini_game.dut.state[2:0]", "bus"), ("level (mode)", "tb_mini_game.mode[1:0]", "bus"),
              ("LED[4:0]", "tb_mini_game.LED[4:0]", "bus")],
             0, 2150, fmt={"LED[4:0]": lambda s: s.zfill(5) if set(s) <= {"0", "1"} else "x",
                           "button[3:0]": lambda s: s.zfill(4) if set(s) <= {"0", "1"} else "x"},
             title="Part 3: four hits on the middle LED (state 3) -> win (state 6, all LEDs on)")

    waveform("lab06_pingpong_wave", sim(f"{L}/bonus-a-ping-pong/sim/tb_ping_pong.vcd"),
             [("clk (game)", "tb_ping_pong.clk", "bit"), ("button[3:0]", "tb_ping_pong.button[3:0]", "bus"),
              ("pos", "tb_ping_pong.dut.pos[2:0]", "bus"), ("direction", "tb_ping_pong.dut.direction", "bit"),
              ("score", "tb_ping_pong.score[3:0]", "bus")],
             0, 1900, fmt={"button[3:0]": lambda s: s.zfill(4) if set(s) <= {"0", "1"} else "x"},
             title="Bonus A: three returns, then a miss resets the score")


def lab04():
    frames_figure("lab04_part3", text_frames(["   5", "   3", "    "]),
                  ["3 + 2 = 5", "1 - 4 = -3  (LED9 = sign)", "7 + 1: overflow (LED0)"], cols=3)
    frames_figure("lab04_part7", [[seg_of_char(c) for c in "   0"], [seg_of_char(c) for c in "   5"],
                                  [seg_of_char(c) for c in "  EE"]],
                  ["no error", "single error at position 5", "double error"], cols=3)


def lab05():
    frames_figure("midterm_bcd", [[seg_of_char(c) for c in "   7"], [seg_of_char(c) for c in "   5"],
                                [seg_of_char(c) for c in "E  E"]],
                  ["3 + 4 = 7", "8 + 7 = 15  (LED0 = tens)", "both inputs invalid"], cols=3)


if __name__ == "__main__":
    lab07(); lab06(); lab04(); lab05()
    print("figures:", ", ".join(sorted(p.name for p in OUT.glob("*.pdf"))))
