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
