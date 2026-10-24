module show4dig (
    input  wire [7:0] Dip,
    output wire       a, b, c, d, e, f, g,
    output wire [3:0] dig
);

    assign dig = 4'b1111;

    Hex_to_7_seg u_dec (
        .Hex(Dip[3:0]),
        .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
    );

endmodule
