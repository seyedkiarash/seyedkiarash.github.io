#!/usr/bin/env python3
"""Generate a constraints.xdc for every part from its top-level ports.

Pin map of the lab board (Zynq-7010, XC7Z010-CLG400) and its extension board,
recovered from the original constraint files and Vivado I/O placement reports.
Usage: scripts/make_xdc.py            (writes <part>/constraints.xdc everywhere)
"""
import re, sys, pathlib

ROOT = pathlib.Path(__file__).resolve().parent.parent

CLOCK_PIN = "U18"                                   # 50 MHz oscillator
BASE_BUTTON = {0: "T10", 1: "T11", 2: "T15", 3: "T14"}
BASE_LED = {0: "V20", 1: "W19", 2: "W18", 3: "V18", 4: "V17"}
EXT_LED = {9: "N15", 8: "N16", 7: "C20", 6: "B20", 5: "E17",
           4: "D18", 3: "E18", 2: "E19", 1: "G17", 0: "G18"}
DIP = {7: "K14", 6: "J14", 5: "M14", 4: "M15", 3: "L19", 2: "L20", 1: "M19", 0: "M20"}
DIG = {3: "D20", 2: "D19", 1: "G20", 0: "B19"}
SEG = {"a": "F16", "b": "F17", "c": "H15", "d": "G15", "e": "J18", "f": "H18", "g": "H16", "dp": "H17"}
PUSH = {1: "J20", 0: "H20"}

# top module of every part (file inside src/)
TOPS = {}

PORT_RE = re.compile(r"\b(input|output)\s+(?:wire|reg)?\s*(\[\s*(\d+)\s*:\s*(\d+)\s*\])?\s*([^;()]*?)(?=,\s*(?:input|output)\b|\)\s*;|$)", re.S)


def ports_of(path, module):
    text = path.read_text()
    m = re.search(r"module\s+%s\b.*?\((.*?)\)\s*;" % re.escape(module), text, re.S)
    body = re.sub(r"//.*", "", m.group(1))
    ports = []
    for direction, rng, msb, lsb, names in PORT_RE.findall(body):
        for n in names.split(","):
            n = re.sub(r"=.*", "", n).strip()
            if n:
                ports.append((n, int(msb) if rng else None, int(lsb) if rng else None))
    return ports


def pins_for(name, msb, lsb):
    width = 1 if msb is None else abs(msb - lsb) + 1
    bits = [None] if msb is None else range(min(msb, lsb), max(msb, lsb) + 1)
    out = []
    for i in bits:
        port = name if i is None else f"{name}[{i}]"
        if name in ("clk", "in_clk"):
            pin = CLOCK_PIN
        elif name == "button":
            pin = BASE_BUTTON[i]
        elif name == "LED":
            pin = EXT_LED[i] if width > 5 else BASE_LED[i]
        elif name == "Dip":
            pin = DIP[i]
        elif name == "dig":
            pin = DIG[i]
        elif name in SEG:
            pin = SEG[name]
        elif name == "Push_button":
            pin = PUSH[i]
        elif name == "gameReset":
            pin = PUSH[0]
        else:
            raise KeyError(f"no pin for {port}")
        out.append((port, pin))
    return out


def main():
    count = 0
    for src in sorted(ROOT.glob("lab*/*/src")):
        part = src.parent
        top_file = part / "TOP"
        if not top_file.exists():
            continue
        module = top_file.read_text().strip()
        path = next(p for p in src.glob("*.v") if re.search(r"module\s+%s\b" % module, p.read_text()))
        lines = [f"## {part.relative_to(ROOT)}  -  top module: {module}",
                 "## Board: Zynq-7010 (XC7Z010-CLG400-1) + extension board, all I/O LVCMOS33", ""]
        has_clock = False
        for name, msb, lsb in ports_of(path, module):
            for port, pin in pins_for(name, msb, lsb):
                lines.append(f"set_property -dict {{PACKAGE_PIN {pin} IOSTANDARD LVCMOS33}} [get_ports {{{port}}}]")
                if name in ("clk", "in_clk"):
                    has_clock = port
        if has_clock:
            lines += ["", f"create_clock -name sys_clk_pin -period 20.000 -waveform {{0.000 10.000}} [get_ports {has_clock}]"]
        (part / "constraints.xdc").write_text("\n".join(lines) + "\n")
        count += 1
    print(f"wrote {count} constraint files")


if __name__ == "__main__":
    main()
