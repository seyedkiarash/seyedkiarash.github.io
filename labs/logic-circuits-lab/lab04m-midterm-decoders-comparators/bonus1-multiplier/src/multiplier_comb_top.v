module multiplier_comb_top (
    input  wire [7:0] Dip,
    output wire [9:0] LED
);
    wire [3:0] A = Dip[3:0];
    wire [3:0] B = Dip[7:4];
    reg  [7:0] product;

    always @(*) begin
        product = 8'd0;
        if (B[0]) product = product + ({4'b0, A} << 0);
        if (B[1]) product = product + ({4'b0, A} << 1);
        if (B[2]) product = product + ({4'b0, A} << 2);
        if (B[3]) product = product + ({4'b0, A} << 3);
    end

    assign LED[7:0] = product;
    assign LED[9:8] = 2'b00;
endmodule
