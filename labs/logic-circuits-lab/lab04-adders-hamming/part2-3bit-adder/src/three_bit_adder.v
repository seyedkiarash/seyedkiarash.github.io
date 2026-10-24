module three_bit_adder (
    input  wire [2:0] A,
    input  wire [2:0] B,
    input  wire       Cin,
    output wire [2:0] S,
    output wire       Cout
);
    wire c1, c2;
    full_adder FA0 (.a(A[0]), .b(B[0]), .cin(Cin), .s(S[0]), .cout(c1));
    full_adder FA1 (.a(A[1]), .b(B[1]), .cin(c1),  .s(S[1]), .cout(c2));
    full_adder FA2 (.a(A[2]), .b(B[2]), .cin(c2),  .s(S[2]), .cout(Cout));
endmodule
