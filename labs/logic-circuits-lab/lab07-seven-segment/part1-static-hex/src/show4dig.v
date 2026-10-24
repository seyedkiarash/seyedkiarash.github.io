// -----------------------------------------------------------------------------
// Lab 7 - Part 1: Static hexadecimal display
// The value on DIP[3:0] is decoded to 7-segment form and shown on all four
// digits at once (every digit enable is driven high, so all digits share the
// same segment lines and therefore show the same character).
// -----------------------------------------------------------------------------
module show4dig (
    input  wire [7:0] Dip,
    output wire       a, b, c, d, e, f, g,
    output wire [3:0] dig
);

    assign dig = 4'b1111;           // enable all four digits

    Hex_to_7_seg u_dec (
        .Hex(Dip[3:0]),
        .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
    );

endmodule
