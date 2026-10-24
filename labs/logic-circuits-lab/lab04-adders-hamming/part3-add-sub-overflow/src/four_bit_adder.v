module four_bit_adder (
    input  wire [3:0] A,
    input  wire [3:0] B,
    input  wire       Op,
    output wire [3:0] S,
    output wire       Cout,
    output wire       Overflow
);
    wire [3:0] B_input = B ^ {4{Op}};
    wire c1, c2, c3;

    full_adder FA0 (.a(A[0]), .b(B_input[0]), .cin(Op), .s(S[0]), .cout(c1));
    full_adder FA1 (.a(A[1]), .b(B_input[1]), .cin(c1), .s(S[1]), .cout(c2));
    full_adder FA2 (.a(A[2]), .b(B_input[2]), .cin(c2), .s(S[2]), .cout(c3));
    full_adder FA3 (.a(A[3]), .b(B_input[3]), .cin(c3), .s(S[3]), .cout(Cout));

    assign Overflow = c3 ^ Cout;
endmodule
