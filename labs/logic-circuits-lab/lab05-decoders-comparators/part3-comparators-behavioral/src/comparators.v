// -----------------------------------------------------------------------------
// Behavioural 4-bit comparators
// -----------------------------------------------------------------------------

// unsigned A > B
module unsigned_checking (
    input  wire [3:0] A,
    input  wire [3:0] B,
    output wire       c
);
    assign c = (A > B);
endmodule

// signed (two's complement) A > B, decided from the sign bits first:
//   A < 0 <= B -> 0;   A >= 0 > B -> 1;   same sign -> compare the low 3 bits
module check_signed_greater (
    input  wire [3:0] A,
    input  wire [3:0] B,
    output reg        c
);
    always @(*) begin
        if (A[3] != B[3]) c = B[3];              // the non-negative one is larger
        else              c = (A[2:0] > B[2:0]);
    end
endmodule

// A == B
module check_signed_equal (
    input  wire [3:0] A,
    input  wire [3:0] B,
    output wire       c
);
    assign c = (A == B);
endmodule
