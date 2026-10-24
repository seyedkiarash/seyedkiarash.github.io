// -----------------------------------------------------------------------------
// Lab 5 - Part 3b: comparators from the flags of a subtractor
//   A = DIP[3:0], B = DIP[7:4], computed A - B
//   LED[0]: A > B unsigned  = C & ~Z
//   LED[1]: A > B signed    = ~Z & (N == V)
//   LED[2]: A == B          = Z
//
// Change from the submitted version: LED[1] was
//   N&~(N^V)&~V | ~N&C&~Z | ~A3&B3
// which is wrong when the subtraction overflows (28 of 256 inputs, e.g.
// A = -8, B = 1 gave "greater"). It is replaced by the standard condition.
// -----------------------------------------------------------------------------
module part52 (
    input  wire [7:0] Dip,
    output wire [9:0] LED
);
    wire z, c, n, v;
    sicom u_cmp (.A(Dip[3:0]), .B(Dip[7:4]), .z(z), .Cout(c), .N(n), .V(v));

    assign LED[0]   = c & ~z;
    assign LED[1]   = ~z & ~(n ^ v);
    assign LED[2]   = z;
    assign LED[9:3] = 7'b0;
endmodule
