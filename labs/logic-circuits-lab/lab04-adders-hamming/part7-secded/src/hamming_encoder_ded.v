// -----------------------------------------------------------------------------
// Extended Hamming (8,4) encoder: Hamming(7,4) plus an overall parity bit
// (SECDED - single error correction, double error detection)
// -----------------------------------------------------------------------------
module hamming_encoder_ded (
    input  wire [3:0] data_in,
    output wire [7:0] encoded_data      // {p_overall, p0, p1, x0, p2, x1, x2, x3}
);
    wire x0 = data_in[3], x1 = data_in[2], x2 = data_in[1], x3 = data_in[0];
    wire [6:0] std_hamming = {x0 ^ x1 ^ x3, x0 ^ x2 ^ x3, x0, x1 ^ x2 ^ x3, x1, x2, x3};

    assign encoded_data = {^std_hamming, std_hamming};
endmodule
