module transmission_line #(parameter integer W = 7) (
    input  wire [W-1:0] data_in,
    input  wire [W-1:0] noise_in,
    output wire [W-1:0] data_out
);
    assign data_out = data_in ^ noise_in;
endmodule
