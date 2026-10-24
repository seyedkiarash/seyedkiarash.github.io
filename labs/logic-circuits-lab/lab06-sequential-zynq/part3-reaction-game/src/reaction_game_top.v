// -----------------------------------------------------------------------------
// Lab 6 - Part 3: Reaction game (top level)
// RTL equivalent of the Vivado block design "system": the game sets the speed
// of its own clock through the level output (mode).
//
//            in_clk (50 MHz)
//                 |
//          +-------------+   out_clk   +-----------+
//          | level_clock |------------>| mini_game |---> LED[4:0]
//          +-------------+             |           |<--- button[3:0], gameReset
//                 ^         mode       |           |
//                 +--------------------+-----------+
// -----------------------------------------------------------------------------
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
