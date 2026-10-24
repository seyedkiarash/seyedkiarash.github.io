// -----------------------------------------------------------------------------
// game_logic  (ping-pong, version 2)
// The light bounces continuously between LED0 and LED4, one step per tick.
// While the light is at an end, the correct button scores a point:
//   at LED4: button[3] -> level + 1,   button[0] -> level = 0
//   at LED0: button[0] -> level + 1,   button[3] -> level = 0
// Reaching level 9 wins: all five LEDs light up until reset.
// Button edges are detected in the 50 MHz domain.
// -----------------------------------------------------------------------------
module game_logic (
    input  wire       clk,
    input  wire       reset,
    input  wire       move_tick,
    input  wire [3:0] button,
    output reg  [4:0] leds,
    output reg  [3:0] level,
    output reg        game_over_flag
);
    reg [2:0] pos;
    reg       direction;
    reg       prev_btn0, prev_btn3;

    wire press_btn0 = button[0] && !prev_btn0;
    wire press_btn3 = button[3] && !prev_btn3;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            level <= 4'd0; pos <= 3'd0; direction <= 1'b0;
            leds  <= 5'b00001;
            prev_btn0 <= 1'b0; prev_btn3 <= 1'b0;
            game_over_flag <= 1'b0;
        end else begin
            prev_btn0 <= button[0];
            prev_btn3 <= button[3];

            if (level >= 4'd9) begin
                leds           <= 5'b11111;          // win
                game_over_flag <= 1'b1;
            end else begin
                leds <= 5'b00001 << pos;

                if (move_tick) begin                 // move the light
                    if (direction == 1'b0) begin
                        if (pos == 3'd4) begin direction <= 1'b1; pos <= 3'd3; end
                        else                     pos <= pos + 3'd1;
                    end else begin
                        if (pos == 3'd0) begin direction <= 1'b0; pos <= 3'd1; end
                        else                     pos <= pos - 3'd1;
                    end
                end

                if (pos == 3'd4) begin               // right end
                    if (press_btn3)      level <= level + 4'd1;
                    else if (press_btn0) level <= 4'd0;
                end
                if (pos == 3'd0) begin               // left end
                    if (press_btn0)      level <= level + 4'd1;
                    else if (press_btn3) level <= 4'd0;
                end
            end
        end
    end
endmodule
