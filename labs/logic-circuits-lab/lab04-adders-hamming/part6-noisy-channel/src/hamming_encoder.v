// -----------------------------------------------------------------------------
// Hamming(7,4) encoder
// Data bits x0..x3 (x0 = data_in[3]) and parity bits p0..p2 are placed in the
// classic positions 1..7 = p0 p1 x0 p2 x1 x2 x3, so that the syndrome of the
// decoder directly gives the position of a single-bit error:
//   p0 covers positions 1,3,5,7   p1 covers 2,3,6,7   p2 covers 4,5,6,7
// -----------------------------------------------------------------------------
module hamming_encoder (
    input  wire [3:0] data_in,
    output wire [6:0] encoded_data      // {p0, p1, x0, p2, x1, x2, x3}
);
    wire x0 = data_in[3], x1 = data_in[2], x2 = data_in[1], x3 = data_in[0];

    wire p0 = x0 ^ x1 ^ x3;
    wire p1 = x0 ^ x2 ^ x3;
    wire p2 = x1 ^ x2 ^ x3;

    assign encoded_data = {p0, p1, x0, p2, x1, x2, x3};
endmodule
