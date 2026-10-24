module Part4_module (
    input  wire [7:0] Dip,
    output wire [9:0] LED
);
    hamming_encoder U_Enc (.data_in(Dip[3:0]), .encoded_data(LED[6:0]));
    assign LED[9:7] = 3'b000;
endmodule
