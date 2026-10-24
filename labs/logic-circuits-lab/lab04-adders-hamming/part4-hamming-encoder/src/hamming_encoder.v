module hamming_encoder (
    input  wire [3:0] data_in,
    output wire [6:0] encoded_data
);
    wire x0 = data_in[3], x1 = data_in[2], x2 = data_in[1], x3 = data_in[0];

    wire p0 = x0 ^ x1 ^ x3;
    wire p1 = x0 ^ x2 ^ x3;
    wire p2 = x1 ^ x2 ^ x3;

    assign encoded_data = {p0, p1, x0, p2, x1, x2, x3};
endmodule
