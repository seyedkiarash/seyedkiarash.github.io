// -----------------------------------------------------------------------------
// Lab 6 - Part 1b: Blinking LED
// A counter divides the 50 MHz clock: the LED toggles every 80,000,000 cycles,
// i.e. every 1.6 s (on 1.6 s, off 1.6 s).
// -----------------------------------------------------------------------------
module led_blink #(
    parameter integer HALF_PERIOD = 80_000_000
) (
    input  wire       clk,
    output reg  [0:0] LED = 1'b0
);
    reg [31:0] counter = 32'd0;

    always @(posedge clk) begin
        if (counter >= HALF_PERIOD - 1) begin
            LED     <= ~LED;
            counter <= 32'd0;
        end else begin
            counter <= counter + 32'd1;
        end
    end
endmodule
