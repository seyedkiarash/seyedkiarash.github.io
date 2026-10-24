module speed_clock (
    input  wire       in_clk,
    input  wire [3:0] mode,
    output reg        out_clk = 1'b0
);
    reg [31:0] count = 32'd0;
    wire [31:0] max_count = (mode <= 4'd9) ? (32'd1 << (26 - mode)) : (32'd1 << 26);

    always @(posedge in_clk) begin
        if (count >= max_count - 1) begin
            out_clk <= ~out_clk;
            count   <= 32'd0;
        end else begin
            count   <= count + 32'd1;
        end
    end
endmodule
