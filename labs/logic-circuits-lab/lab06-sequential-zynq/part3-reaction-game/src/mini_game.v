// -----------------------------------------------------------------------------
// mini_game  (miniGame in the block design)
// A light runs across the 5 LEDs (states 1..5, LED0 -> LED4, then repeats).
// Press button[2] while the MIDDLE LED (state 3) is lit:
//   * hit  -> next level (the light gets faster) and the run restarts;
//             a hit on level 3 wins the game (state 6: all LEDs on)
//   * miss (pressed on any other LED) -> back to level 0
// In the win state, another press starts a new game. gameReset restarts too.
// The module is clocked by the level-dependent clock from level_clock.
// -----------------------------------------------------------------------------
module mini_game (
    input  wire       clk,
    input  wire       gameReset,
    input  wire [3:0] button,
    output reg  [4:0] LED,
    output wire [1:0] mode             // current level -> selects the speed
);
    reg [1:0] level   = 2'd0;
    reg [2:0] state   = 3'd1;
    reg       last_b2 = 1'b0;

    wire press = button[2] & ~last_b2;  // button went high since the last step

    always @(posedge clk or posedge gameReset) begin
        if (gameReset) begin
            state   <= 3'd1;
            level   <= 2'd0;
            last_b2 <= 1'b0;
        end else begin
            last_b2 <= button[2];
            if (state == 3'd6) begin                 // win state
                if (press) begin
                    state <= 3'd1;
                    level <= 2'd0;
                end
            end else if (press) begin
                if (state == 3'd3) begin             // hit
                    if (level == 2'd3) state <= 3'd6;
                    else begin
                        level <= level + 2'd1;
                        state <= 3'd1;
                    end
                end else begin                       // miss
                    level <= 2'd0;
                    state <= 3'd1;
                end
            end else begin
                state <= (state == 3'd5) ? 3'd1 : state + 3'd1;
            end
        end
    end

    assign mode = level;

    always @(*) begin
        case (state)
            3'd1: LED = 5'b00001;
            3'd2: LED = 5'b00010;
            3'd3: LED = 5'b00100;
            3'd4: LED = 5'b01000;
            3'd5: LED = 5'b10000;
            3'd6: LED = 5'b11111;
            default: LED = 5'b00000;
        endcase
    end
endmodule
