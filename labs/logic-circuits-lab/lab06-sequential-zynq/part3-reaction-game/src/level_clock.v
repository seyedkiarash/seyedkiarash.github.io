module level_clock (
    input  wire       in_clk,
    input  wire [1:0] mode,
    output reg        out_clk = 1'b0
);
    reg [23:0] count = 24'd0;
    reg [23:0] max_count;

    always @(*) begin
        case (mode)
            2'd0: max_count = 24'd6_250_000;
            2'd1: max_count = 24'd4_166_666;
            2'd2: max_count = 24'd3_125_000;
            2'd3: max_count = 24'd2_500_000;
        endcase
    end

    always @(posedge in_clk) begin
        if (count >= max_count - 1) begin
            out_clk <= ~out_clk;
            count   <= 24'd0;
        end else begin
            count   <= count + 24'd1;
        end
    end
endmodule
