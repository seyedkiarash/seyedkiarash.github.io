// check10: high when a 4-bit value is not a valid BCD digit (>= 10)
// 1010..1111 are exactly the codes with A3 = 1 and (A2 = 1 or A1 = 1).
module check10 (
    input  wire [3:0] A,
    output wire       b
);
    assign b = (A[3] & A[2]) | (A[3] & A[1]);
endmodule
