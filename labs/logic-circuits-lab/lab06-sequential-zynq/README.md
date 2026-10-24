# Experiment 6 — Clock division, LED patterns, games, Zynq PS clocking

Report: [`../reports/lab06.pdf`](../reports/lab06.pdf)

| Part | What it does | Top module | Testbench |
|---|---|---|---|
| [`part1a-clock-on-led`](part1a-clock-on-led/) | the 50 MHz clock on an LED | `clk_led` | `tb_clk_led` |
| [`part1b-led-blink`](part1b-led-blink/) | counter-based blinking LED (1.6 s) | `led_blink` | `tb_led_blink` |
| [`part2-led-flow`](part2-led-flow/) | 10-state LED pattern with button speed control | `led_flow` | `tb_led_flow` |
| [`part3-reaction-game`](part3-reaction-game/) | reaction game; the game level sets its own clock (block design) | `reaction_game_top` | `tb_mini_game` |
| [`part4-zynq-ps-clock`](part4-zynq-ps-clock/) | LED flow clocked by the Zynq PS (FCLK_CLK0, block design) | `led_flow` | `tb_led_flow` |
| [`bonus-a-ping-pong`](bonus-a-ping-pong/) | ping-pong with a level-controlled clock and score display | `ping_pong_top` | `tb_ping_pong` |
| [`bonus-b-ping-pong-v2`](bonus-b-ping-pong-v2/) | ping-pong in one clock domain with debounced buttons (**completed**) | `ping_pong_v2_top` | `tb_ping_pong_v2` |

Each part folder contains `src/` (Verilog), `sim/` (self-checking testbench) and `constraints.xdc`
(pins for the Zynq-7010 board + extension board). Shared modules are in [`../common`](../common).
