module Part1_module (
    input  wire [7:0] Dip,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g
);
    Hex_to_7_seg u_hex (.Hex(Dip[3:0]), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));
    assign dig = 4'b0001;
endmodule
