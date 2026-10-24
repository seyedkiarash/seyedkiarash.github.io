module clock_divider #(
    parameter integer HALF_PERIOD = 12_500
) (
    input  wire clk,
    output reg  clk_out = 1'b0
);

    reg [31:0] count = 32'd0;

    always @(posedge clk) begin
        if (count >= HALF_PERIOD - 1) begin
            clk_out <= ~clk_out;
            count   <= 32'd0;
        end else begin
            count   <= count + 32'd1;
        end
    end

endmodule
