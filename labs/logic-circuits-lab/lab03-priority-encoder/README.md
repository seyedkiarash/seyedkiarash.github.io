# Experiment 3 — Priority encoder

Report: [`../reports/lab03.pdf`](../reports/lab03.pdf)

| Part | What it does | Top module | Testbench |
|---|---|---|---|
| [`part3-active-high`](part3-active-high/) | 4-input priority encoder, buttons used directly | `priority_encoder` | `tb_priority_encoder` |
| [`part5-active-low`](part5-active-low/) | same encoder with the active-low board buttons inverted | `part5` | `tb_part5` |

Each part folder contains `src/` (Verilog), `sim/` (self-checking testbench) and `constraints.xdc`
(pins for the Zynq-7010 board + extension board). Shared modules live in [`../common`](../common).
Run the testbenches with `../scripts/run_sims.sh .` from this folder.
