module reaction_game_top (
    input  wire       in_clk,
    input  wire       gameReset,
    input  wire [3:0] button,
    output wire [4:0] LED
);
    wire       game_clk;
    wire [1:0] mode;

    level_clock u_clk  (.in_clk(in_clk), .mode(mode), .out_clk(game_clk));
    mini_game   u_game (.clk(game_clk), .gameReset(gameReset), .button(button),
                        .LED(LED), .mode(mode));
endmodule
