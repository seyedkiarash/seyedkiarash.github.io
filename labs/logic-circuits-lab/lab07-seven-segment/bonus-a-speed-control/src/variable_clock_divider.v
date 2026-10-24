// -----------------------------------------------------------------------------
// variable_clock_divider
// Like clock_divider, but the half-period can be changed at run time:
//   rising edge on button[1] -> half-period x2  (stopwatch runs slower)
//   rising edge on button[2] -> half-period /2  (stopwatch runs faster)
// Edges are detected by comparing each button with its value one clock earlier.
// -----------------------------------------------------------------------------
module variable_clock_divider #(
    parameter integer INITIAL_HALF_PERIOD = 5_000_000   // 5 Hz at 50 MHz
) (
    input  wire       clk,
    input  wire [3:0] button,
    output reg        clk_out = 1'b0
);

    reg [31:0] count     = 32'd0;
    reg [31:0] max_count = INITIAL_HALF_PERIOD;
    reg        last_b1   = 1'b0;
    reg        last_b2   = 1'b0;

    always @(posedge clk) begin
        last_b1 <= button[1];
        last_b2 <= button[2];
        if (button[1] & ~last_b1)
            max_count <= max_count << 1;          // slower
        else if (button[2] & ~last_b2)
            max_count <= max_count >> 1;          // faster
    end

    always @(posedge clk) begin
        if (count >= max_count - 1) begin
            clk_out <= ~clk_out;
            count   <= 32'd0;
        end else begin
            count   <= count + 32'd1;
        end
    end

endmodule
