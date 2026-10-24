// -----------------------------------------------------------------------------
// Basic adder cells shared by Labs 4 and 5.
// -----------------------------------------------------------------------------

// Half adder: s = a xor b, c = a and b
module half_adder (
    input  wire a,
    input  wire b,
    output wire s,
    output wire c
);
    assign s = a ^ b;
    assign c = a & b;
endmodule

// Full adder built from two half adders
module full_adder (
    input  wire a,
    input  wire b,
    input  wire cin,
    output wire s,
    output wire cout
);
    wire s1, c1, c2;

    half_adder HA1 (.a(a),  .b(b),   .s(s1), .c(c1));
    half_adder HA2 (.a(s1), .b(cin), .s(s),  .c(c2));

    assign cout = c1 | c2;
endmodule

// 4-bit ripple-carry adder
module adder_4bit (
    input  wire [3:0] A,
    input  wire [3:0] B,
    input  wire       Cin,
    output wire [3:0] s,
    output wire       Cout
);
    wire c1, c2, c3;

    full_adder FA0 (.a(A[0]), .b(B[0]), .cin(Cin), .s(s[0]), .cout(c1));
    full_adder FA1 (.a(A[1]), .b(B[1]), .cin(c1),  .s(s[1]), .cout(c2));
    full_adder FA2 (.a(A[2]), .b(B[2]), .cin(c2),  .s(s[2]), .cout(c3));
    full_adder FA3 (.a(A[3]), .b(B[3]), .cin(c3),  .s(s[3]), .cout(Cout));
endmodule
