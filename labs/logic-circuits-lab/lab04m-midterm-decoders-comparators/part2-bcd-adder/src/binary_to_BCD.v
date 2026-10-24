module binary_to_BCD (
    input  wire [3:0] S,
    input  wire [3:0] A,
    input  wire [3:0] B,
    input  wire       Cout,
    output reg  [3:0] yekan,
    output reg        dahgan,
    output reg        t
);
    wire bad_a, bad_b;
    check10 u_ca (.A(A), .b(bad_a));
    check10 u_cb (.A(B), .b(bad_b));

    always @(*) begin
        t = 1'b0; dahgan = 1'b0; yekan = S;
        if (bad_a | bad_b) begin
            yekan = 4'hE;
            t     = bad_a & bad_b;
        end else if (Cout) begin
            dahgan = 1'b1;
            yekan  = {1'b1, S} - 5'd10;
        end else if (S >= 4'd10) begin
            dahgan = 1'b1;
            yekan  = S - 4'd10;
        end
    end
endmodule
