# Logic Circuits Laboratory — FPGA designs

**Seyed Kiarash Eshraghi Naeini** · Department of Electrical Engineering, Sharif University of Technology · Fall 2025  
Instructor: Dr. Mohammad Reza Movahhedin · Teaching assistant: Hossein Moghim

Verilog designs from the Logic Circuits Laboratory, implemented on a **Zynq-7010 (XC7Z010-CLG400-1)** board
with a 50 MHz clock and an extension board (8 DIP switches, 4-digit seven-segment display, 10 LEDs,
push buttons). The original Vivado 2019.1 projects were cleaned up, documented, re-verified in simulation
and written up as one report per experiment.

| Experiment | Topics | Report |
|---|---|---|
| [3](lab03-priority-encoder/) | priority encoder, push-button polarity | [PDF](reports/lab03.pdf) |
| [4](lab04-adders-hamming/) | half/full adders, ripple-carry adder, two's-complement overflow, Hamming(7,4), SECDED | [PDF](reports/lab04.pdf) |
| [Midterm](lab04m-midterm-decoders-comparators/) | decoder, BCD adder, comparators (behavioural and from subtractor flags), multiplexer, multiplier, mux-only comparator | [PDF](reports/midterm.pdf) |
| [6](lab06-sequential-zynq/) | clock division, LED patterns, games, block designs, PL clock from the Zynq PS | [PDF](reports/lab06.pdf) |
| [7](lab07-seven-segment/) | seven-segment multiplexing, scrolling text, stopwatch, snake animation | [PDF](reports/lab07.pdf) |

## Verification

* **32 self-checking testbenches** (Icarus Verilog), one per design — exhaustive for every combinational
  design (all input combinations, all single/double error patterns for the Hamming codes) and
  scenario-based for the sequential ones (e.g. a full 10-minute stopwatch cycle).
  Run all of them with `scripts/run_sims.sh`.
* **Synthesis check** of every design with Yosys (`scripts/synth_check.sh`, results in
  [`docs/synth_check.txt`](docs/synth_check.txt)): no errors, no inferred latches.
* Resource and timing figures in the reports come from the Vivado implementation reports of the lab
  sessions; every clocked design met the 20 ns constraint (worst slack ≥ 13 ns).

Verification found errors in the submitted code; they are corrected here and described in the reports
(midterm: signed comparator from subtractor flags, the wiring of the multiplexer comparator;
Experiment 7: one digit of the student number, mirrored scrolling windows). Two bonus designs that were
left unfinished in the lab — the snake animation (Experiment 7) and the second ping-pong game
(Experiment 6) — were completed.

## Layout

```
common/            shared modules: Hex_to_7_seg, clock_divider, half/full adders
labNN-*/partX/     src/ (design)  sim/ (testbench)  constraints.xdc  TOP (top module)
reports/           LaTeX sources and PDFs of the reports, figures generated from the simulations
scripts/           run_sims.sh, synth_check.sh, make_xdc.py, figures.py
```

To rebuild a design in Vivado: create an RTL project for part `xc7z010clg400-1`, add `common/*.v` and the
part's `src/*.v` as sources and `constraints.xdc` as constraints, and set the top module named in `TOP`.
The block-design parts also include the original `.bd` files in `vivado/`.
