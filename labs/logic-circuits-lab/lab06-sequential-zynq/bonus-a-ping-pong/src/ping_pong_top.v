module ping_pong_top (
    input  wire       in_clk,
    input  wire       gameReset,
    input  wire [3:0] button,
    output wire [4:0] LED,
    output wire       a, b, c, d, e, f, g
);
    wire       game_clk;
    wire [3:0] mode, score;

    speed_clock u_clk  (.in_clk(in_clk), .mode(mode), .out_clk(game_clk));
    ping_pong   u_game (.clk(game_clk), .gameReset(gameReset), .button(button),
                        .LED(LED), .mode(mode), .score(score));
    Hex_to_7_seg u_dec (.Hex(score), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));
endmodule
