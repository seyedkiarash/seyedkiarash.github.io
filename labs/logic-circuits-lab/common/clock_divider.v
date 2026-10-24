// -----------------------------------------------------------------------------
// clock_divider
// Generates a slow square wave from the 50 MHz board clock.
//
// The output toggles every HALF_PERIOD input cycles, so
//
//     f_out = f_clk / (2 * HALF_PERIOD)
//
//   HALF_PERIOD = 12_500       ->  2 kHz   (7-segment multiplexing)
//   HALF_PERIOD = 2_500_000    ->  10 Hz   (stopwatch tick)
//   HALF_PERIOD = 12_500_000   ->  2 Hz
//   HALF_PERIOD = 50_000_000   ->  0.5 Hz
//
// (In the lab this module was called freq_converter with the count stored in
//  a register; it is a parameter here so the testbenches can shorten it.)
// -----------------------------------------------------------------------------
module clock_divider #(
    parameter integer HALF_PERIOD = 12_500
) (
    input  wire clk,
    output reg  clk_out = 1'b0
);

    reg [31:0] count = 32'd0;

    always @(posedge clk) begin
        if (count >= HALF_PERIOD - 1) begin
            clk_out <= ~clk_out;
            count   <= 32'd0;
        end else begin
            count   <= count + 32'd1;
        end
    end

endmodule
