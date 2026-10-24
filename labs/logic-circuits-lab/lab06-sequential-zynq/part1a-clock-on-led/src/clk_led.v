module clk_led (
    input  wire       clk,
    output wire [0:0] LED
);
    assign LED[0] = clk;
endmodule
