// -----------------------------------------------------------------------------
// sicom: computes A - B = A + ~B + 1 with the 4-bit adder and returns the
// status flags used for comparisons:
//   z    : result is zero            (A == B)
//   Cout : no borrow                 (A >= B unsigned)
//   N    : sign bit of the result
//   V    : two's-complement overflow of the SUBTRACTION
//
// Change from the submitted version: V used the overflow formula of an
// ADDITION of A and B. For A - B the operands of the adder are A and ~B, so
//   V = (A3 & ~B3 & ~S3) | (~A3 & B3 & S3)
// -----------------------------------------------------------------------------
module sicom (
    input  wire [3:0] A,
    input  wire [3:0] B,
    output wire       z, Cout, N, V
);
    wire [3:0] s;
    adder_4bit u_sub (.A(A), .B(~B), .Cin(1'b1), .s(s), .Cout(Cout));

    assign z = (s == 4'b0000);
    assign N = s[3];
    assign V = (A[3] & ~B[3] & ~s[3]) | (~A[3] & B[3] & s[3]);
endmodule
