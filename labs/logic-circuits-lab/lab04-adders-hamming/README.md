# Experiment 4 — Adders, overflow and Hamming codes

Report: [`../reports/lab04.pdf`](../reports/lab04.pdf)

| Part | What it does | Top module | Testbench |
|---|---|---|---|
| [`part1-hex-display`](part1-hex-display/) | hex digit on a 7-segment display (also packaged as an IP / block design) | `Part1_module` | `tb_part1` |
| [`part2-3bit-adder`](part2-3bit-adder/) | 3-bit ripple-carry adder from half/full adders | `Part2_module` | `tb_part2` |
| [`part3-add-sub-overflow`](part3-add-sub-overflow/) | 4-bit two's-complement adder/subtractor, overflow, sign-magnitude display | `Part3_module` | `tb_part3` |
| [`part4-hamming-encoder`](part4-hamming-encoder/) | Hamming(7,4) encoder | `Part4_module` | `tb_part4` |
| [`part5-hamming-decoder`](part5-hamming-decoder/) | Hamming(7,4) decoder with single-error correction | `Part5_module` | `tb_part5` |
| [`part6-noisy-channel`](part6-noisy-channel/) | encoder → noisy channel (switches/buttons) → decoder | `Part6_module` | `tb_part6` |
| [`part7-secded`](part7-secded/) | extended Hamming(8,4): single-error correction, double-error detection | `Part7_module` | `tb_part7` |

Each part folder contains `src/` (Verilog), `sim/` (self-checking testbench) and `constraints.xdc`
(pins for the Zynq-7010 board + extension board). Shared modules live in [`../common`](../common).
Run the testbenches with `../scripts/run_sims.sh .` from this folder.
