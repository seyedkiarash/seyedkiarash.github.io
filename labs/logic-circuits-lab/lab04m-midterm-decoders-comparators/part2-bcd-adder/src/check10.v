module check10 (
    input  wire [3:0] A,
    output wire       b
);
    assign b = (A[3] & A[2]) | (A[3] & A[1]);
endmodule
