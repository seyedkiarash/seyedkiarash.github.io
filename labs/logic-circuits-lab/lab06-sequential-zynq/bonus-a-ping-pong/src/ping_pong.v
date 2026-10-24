// -----------------------------------------------------------------------------
// ping_pong  (GAME in the block design)
// The light bounces between LED0 and LED4. When it reaches an end, the player
// on that side must have pressed his button during that step:
//   LED4 end -> button[3],  LED0 end -> button[0]
// A return increases the level (max 9), which speeds up the clock; a miss
// resets the level to 0 and restarts from LED0. The level is also the score.
// Runs on the level-dependent clock from speed_clock.
// -----------------------------------------------------------------------------
module ping_pong (
    input  wire       clk,
    input  wire       gameReset,
    input  wire [3:0] button,
    output reg  [4:0] LED,
    output wire [3:0] mode,
    output wire [3:0] score
);
    reg [3:0] level     = 4'd0;
    reg [2:0] pos       = 3'd0;    // 0..4
    reg       direction = 1'b0;    // 0: towards LED4, 1: towards LED0
    reg       last_b0   = 1'b0;
    reg       last_b3   = 1'b0;

    always @(posedge clk or posedge gameReset) begin
        if (gameReset) begin
            level <= 4'd0; pos <= 3'd0; direction <= 1'b0;
            last_b0 <= 1'b0; last_b3 <= 1'b0;
        end else begin
            last_b0 <= button[0];
            last_b3 <= button[3];
            if (direction == 1'b0) begin
                if (pos < 3'd4)
                    pos <= pos + 3'd1;
                else if (button[3] && !last_b3) begin      // returned at LED4
                    if (level < 4'd9) level <= level + 4'd1;
                    direction <= 1'b1;
                    pos       <= 3'd3;
                end else begin                             // missed
                    level <= 4'd0; pos <= 3'd0; direction <= 1'b0;
                end
            end else begin
                if (pos > 3'd0)
                    pos <= pos - 3'd1;
                else if (button[0] && !last_b0) begin      // returned at LED0
                    if (level < 4'd9) level <= level + 4'd1;
                    direction <= 1'b0;
                    pos       <= 3'd1;
                end else begin                             // missed
                    level <= 4'd0; pos <= 3'd0; direction <= 1'b0;
                end
            end
        end
    end

    always @(*) LED = 5'b00001 << pos;

    assign mode  = level;
    assign score = level;
endmodule
