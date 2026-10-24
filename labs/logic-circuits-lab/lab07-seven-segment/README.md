# Experiment 7 — Seven-segment multiplexing and a stopwatch

Report: [`../reports/lab07.pdf`](../reports/lab07.pdf)

| Part | What it does | Top module | Testbench |
|---|---|---|---|
| [`part1-static-hex`](part1-static-hex/) | hex value on all four digits | `show4dig` | `tb_show4dig` |
| [`part2-student-id`](part2-student-id/) | student number digit by digit at 2 Hz (**fixed** digit 4) | `show_student_id` | `tb_show_student_id` |
| [`part3-multiplexing`](part3-multiplexing/) | time-multiplexed "1234" at 2 kHz scan / 500 Hz refresh | `display_1234` | `tb_display_1234` |
| [`part4-moving-digit`](part4-moving-digit/) | a digit moving across the display | `moving_digit` | `tb_moving_digit` |
| [`part5-scrolling-id`](part5-scrolling-id/) | scrolling student number (**fixed** mirrored windows) | `scrolling_student_id` | `tb_scrolling_student_id` |
| [`part6-stopwatch`](part6-stopwatch/) | stopwatch M SS.d from cascaded modulo counters | `stopwatch` | `tb_stopwatch` |
| [`bonus-a-speed-control`](bonus-a-speed-control/) | stopwatch with run-time speed control | `stopwatch_speed_control` | `tb_stopwatch_speed_control` |
| [`bonus-b-start-stop-reset`](bonus-b-start-stop-reset/) | stopwatch with start / stop / reset | `stopwatch_start_stop` | `tb_stopwatch_start_stop` |
| [`bonus-c-snake`](bonus-c-snake/) | a 3-segment snake around the display (**completed**) | `snake_display` | `tb_snake_display` |

Each part folder contains `src/` (Verilog), `sim/` (self-checking testbench) and `constraints.xdc`
(pins for the Zynq-7010 board + extension board). Shared modules are in [`../common`](../common).
