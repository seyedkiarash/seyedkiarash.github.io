module encoderpr (
    input  wire [3:0] A,
    output reg  [2:0] c
);
    always @(*) begin
        if      (A[3]) c = 3'b100;
        else if (A[2]) c = 3'b011;
        else if (A[1]) c = 3'b010;
        else if (A[0]) c = 3'b001;
        else           c = 3'b000;
    end
endmodule
