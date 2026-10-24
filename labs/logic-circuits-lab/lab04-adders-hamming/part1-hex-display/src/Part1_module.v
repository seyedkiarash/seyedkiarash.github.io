// -----------------------------------------------------------------------------
// Lab 4 - Part 1: Hexadecimal digit on one 7-segment display
// DIP[3:0] is shown as 0-F on the rightmost digit.
// (In the lab this module was also packaged as an IP and placed in a block
//  design - see ../vivado/design_1.bd.)
// -----------------------------------------------------------------------------
module Part1_module (
    input  wire [7:0] Dip,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g
);
    Hex_to_7_seg u_hex (.Hex(Dip[3:0]), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));
    assign dig = 4'b0001;
endmodule
