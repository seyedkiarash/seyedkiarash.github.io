module unsigned_checking (
    input  wire [3:0] A,
    input  wire [3:0] B,
    output wire       c
);
    assign c = (A > B);
endmodule

module check_signed_greater (
    input  wire [3:0] A,
    input  wire [3:0] B,
    output reg        c
);
    always @(*) begin
        if (A[3] != B[3]) c = B[3];
        else              c = (A[2:0] > B[2:0]);
    end
endmodule

module check_signed_equal (
    input  wire [3:0] A,
    input  wire [3:0] B,
    output wire       c
);
    assign c = (A == B);
endmodule
