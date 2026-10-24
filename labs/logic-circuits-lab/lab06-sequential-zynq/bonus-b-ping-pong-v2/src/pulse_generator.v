// -----------------------------------------------------------------------------
// pulse_generator
// Produces a one-clock-cycle 'tick' every (max_count + 1) cycles of the 50 MHz
// clock. The game logic then runs on the 50 MHz clock and only advances on
// ticks (clock-enable style) instead of using a divided clock.
//   level 0: 0.2 s per step, each level halves it, level >= 9: 0.4 ms
// -----------------------------------------------------------------------------
module pulse_generator (
    input  wire       clk,
    input  wire       reset,
    input  wire [3:0] level,
    output reg        tick
);
    reg [31:0] counter;
    reg [31:0] max_count;

    always @(*) begin
        case (level)
            4'd0: max_count = 32'd10_000_000;
            4'd1: max_count = 32'd5_000_000;
            4'd2: max_count = 32'd2_500_000;
            4'd3: max_count = 32'd1_250_000;
            4'd4: max_count = 32'd625_000;
            4'd5: max_count = 32'd312_500;
            4'd6: max_count = 32'd156_250;
            4'd7: max_count = 32'd78_125;
            4'd8: max_count = 32'd39_000;
            default: max_count = 32'd20_000;
        endcase
    end

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            counter <= 32'd0;
            tick    <= 1'b0;
        end else if (counter >= max_count) begin
            counter <= 32'd0;
            tick    <= 1'b1;
        end else begin
            counter <= counter + 32'd1;
            tick    <= 1'b0;
        end
    end
endmodule
