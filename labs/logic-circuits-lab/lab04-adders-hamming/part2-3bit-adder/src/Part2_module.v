// -----------------------------------------------------------------------------
// Lab 4 - Part 2: 3-bit adder with the result on a 7-segment digit
//   A = DIP[3:1], B = DIP[6:4], Cin = DIP[7]
// The 4-bit result {Cout, S} (0..15) is shown in hex on the leftmost digit.
// -----------------------------------------------------------------------------
module Part2_module (
    input  wire [7:0] Dip,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g
);
    wire [2:0] S;
    wire       Cout;

    three_bit_adder u_adder (.A(Dip[3:1]), .B(Dip[6:4]), .Cin(Dip[7]), .S(S), .Cout(Cout));
    Hex_to_7_seg    u_hex   (.Hex({Cout, S}), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

    assign dig = 4'b1000;
endmodule
