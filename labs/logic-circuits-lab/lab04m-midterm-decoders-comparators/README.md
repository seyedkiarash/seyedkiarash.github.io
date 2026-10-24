# Midterm experiment — Decoders, BCD addition, comparators, multiplexers

Report: [`../reports/midterm.pdf`](../reports/midterm.pdf)

| Part | What it does | Top module | Testbench |
|---|---|---|---|
| [`part1-decoder-3to8`](part1-decoder-3to8/) | 3-to-8 decoder (gate level) | `part1` | `tb_part1` |
| [`part2-bcd-adder`](part2-bcd-adder/) | one-digit BCD adder with invalid-input detection | `part2` | `tb_part2` |
| [`part3-comparators-behavioral`](part3-comparators-behavioral/) | unsigned / signed / equality comparators (behavioural) | `part3` | `tb_part3` |
| [`part3b-comparators-subtractor`](part3b-comparators-subtractor/) | comparators from subtractor flags Z, C, N, V (**fixed**) | `part52` | `tb_part52` |
| [`part4-mux-8to1`](part4-mux-8to1/) | 8-to-1 multiplexer | `part4` | `tb_part4` |
| [`bonus1-multiplier`](bonus1-multiplier/) | 4×4 shift-and-add multiplier | `multiplier_comb_top` | `tb_multiplier` |
| [`bonus2-mux-logic`](bonus2-mux-logic/) | 2-bit comparator built only from 8-to-1 multiplexers (**fixed**) | `bonus2` | `tb_bonus2` |

Each part folder contains `src/` (Verilog), `sim/` (self-checking testbench) and `constraints.xdc`
(pins for the Zynq-7010 board + extension board). Shared modules are in [`../common`](../common).
