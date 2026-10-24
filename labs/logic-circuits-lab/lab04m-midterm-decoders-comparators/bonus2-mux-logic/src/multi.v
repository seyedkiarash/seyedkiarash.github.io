module multi (
    input  wire [7:0] A,
    input  wire [2:0] s,
    output wire       f
);
    assign f = A[s];
endmodule
