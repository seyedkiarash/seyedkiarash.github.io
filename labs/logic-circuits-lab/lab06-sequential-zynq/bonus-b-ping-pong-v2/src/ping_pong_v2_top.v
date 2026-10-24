// -----------------------------------------------------------------------------
// Lab 6 - Bonus B: Ping-pong, version 2 (single clock domain)
// Everything runs on the 50 MHz clock; pulse_generator provides the movement
// ticks (clock enables) whose rate depends on the level. The level is shown on
// one 7-segment digit.
//
// Note: the digit enables are driven as 1110 (active-low digit 0), as in the
// submitted version; Lab 7 Parts 3-6 drive them active-high (0001).
// -----------------------------------------------------------------------------
module ping_pong_v2_top (
    input  wire       in_clk,
    input  wire       gameReset,
    input  wire [3:0] button,
    output wire [4:0] LED,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g, dp
);
    wire       move_tick;
    wire [3:0] level;
    wire       game_over;

    pulse_generator u_pg (.clk(in_clk), .reset(gameReset), .level(level), .tick(move_tick));

    game_logic u_game (.clk(in_clk), .reset(gameReset), .move_tick(move_tick),
                       .button(button), .leds(LED), .level(level),
                       .game_over_flag(game_over));

    Hex_to_7_seg u_dec (.Hex(level), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

    assign dp  = 1'b1;          // decimal point off
    assign dig = 4'b1110;
endmodule
