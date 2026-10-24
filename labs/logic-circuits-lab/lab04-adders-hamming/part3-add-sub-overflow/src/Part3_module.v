// -----------------------------------------------------------------------------
// Lab 4 - Part 3: Signed adder / subtractor with overflow indication
//   A = DIP[7:4], B = DIP[3:0] (4-bit two's complement, -8..7)
//   Push_button[1] selects the operation (0: A+B, 1: A-B)
// Output:
//   * magnitude of the result on the rightmost 7-segment digit
//   * LED[9] = minus sign
//   * LED[0] = overflow; on overflow the digit is switched off
// -----------------------------------------------------------------------------
module Part3_module (
    input  wire [7:0] Dip,
    input  wire [1:0] Push_button,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g,
    output wire [9:0] LED
);
    wire [3:0] sum, mag;
    wire       cout, overflow, sign;

    four_bit_adder   U_ALU (.A(Dip[7:4]), .B(Dip[3:0]), .Op(Push_button[1]),
                            .S(sum), .Cout(cout), .Overflow(overflow));
    twos_to_sign_mag U_Cnv (.TwosComp(sum), .Sign(sign), .Mag(mag));
    Hex_to_7_seg     U_Hex (.Hex(mag), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

    assign dig      = {3'b000, ~overflow};
    assign LED[0]   = overflow;
    assign LED[9]   = ~overflow & sign;
    assign LED[8:1] = 8'b0;
endmodule
