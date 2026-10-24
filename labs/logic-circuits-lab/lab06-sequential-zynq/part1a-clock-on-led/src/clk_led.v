// -----------------------------------------------------------------------------
// Lab 6 - Part 1a: The board clock on an LED
// The LED simply follows the 50 MHz clock. It toggles far too fast for the eye,
// so the LED looks steadily lit at about half brightness - the motivation for
// the clock divider of Part 1b.
// (Vivado warns about a clock net driving an output; that is expected here.)
// -----------------------------------------------------------------------------
module clk_led (
    input  wire       clk,
    output wire [0:0] LED
);
    assign LED[0] = clk;
endmodule
