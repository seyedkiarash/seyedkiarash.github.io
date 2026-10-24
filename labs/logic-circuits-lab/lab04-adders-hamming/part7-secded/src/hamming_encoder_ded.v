module hamming_encoder_ded (
    input  wire [3:0] data_in,
    output wire [7:0] encoded_data
);
    wire x0 = data_in[3], x1 = data_in[2], x2 = data_in[1], x3 = data_in[0];
    wire [6:0] std_hamming = {x0 ^ x1 ^ x3, x0 ^ x2 ^ x3, x0, x1 ^ x2 ^ x3, x1, x2, x3};

    assign encoded_data = {^std_hamming, std_hamming};
endmodule
