// -----------------------------------------------------------------------------
// Lab 5 - Part 2: BCD adder
//   A = DIP[3:0], B = DIP[7:4] (decimal digits 0..9)
//   units digit -> 7-segment digit 0, tens -> LED[0]
//   invalid input -> "E" (on two digits if both inputs are invalid)
// -----------------------------------------------------------------------------
module part2 (
    input  wire [7:0] Dip,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g,
    output wire [9:0] LED
);
    wire [3:0] S, units;
    wire       Cout, tens, both_bad;

    adder_4bit    u_add (.A(Dip[3:0]), .B(Dip[7:4]), .Cin(1'b0), .s(S), .Cout(Cout));
    binary_to_BCD u_bcd (.S(S), .A(Dip[3:0]), .B(Dip[7:4]), .Cout(Cout),
                         .yekan(units), .dahgan(tens), .t(both_bad));
    Hex_to_7_seg  u_hex (.Hex(units), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

    assign LED[0]   = tens;
    assign LED[9:1] = 9'b0;
    assign dig      = {both_bad, 3'b001};
endmodule
