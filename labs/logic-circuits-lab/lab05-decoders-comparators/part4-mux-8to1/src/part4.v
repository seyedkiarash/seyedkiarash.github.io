// -----------------------------------------------------------------------------
// Lab 5 - Part 4: 8-to-1 multiplexer
// The DIP switches are the 8 data inputs; the three (active-low) push buttons
// button[2:0] form the select code. The selected bit is shown on LED[0].
// -----------------------------------------------------------------------------
module part4 (
    input  wire [7:0] Dip,
    input  wire [3:0] button,
    output wire [4:0] LED
);
    multi m1 (.A(Dip), .s(~button[2:0]), .f(LED[0]));
    assign LED[4:1] = 4'b0;
endmodule
