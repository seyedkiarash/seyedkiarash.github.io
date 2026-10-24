// -----------------------------------------------------------------------------
// Hamming(7,4) decoder with single-error correction
// The three parity checks form the syndrome {c2,c1,c0} = position (1..7) of a
// single flipped bit, or 0 if no error. Flipped data bits (positions 3,5,6,7)
// are corrected; the syndrome is also output for display.
// -----------------------------------------------------------------------------
module hamming_decoder (
    input  wire [6:0] received_data,    // {p0, p1, x0, p2, x1, x2, x3}
    output wire [3:0] corrected_data,   // {x0, x1, x2, x3}
    output wire [3:0] error_loc         // 0 = no error, 1..7 = bit position
);
    wire p0 = received_data[6], p1 = received_data[5], x0 = received_data[4];
    wire p2 = received_data[3], x1 = received_data[2], x2 = received_data[1];
    wire x3 = received_data[0];

    wire c0 = p0 ^ x0 ^ x1 ^ x3;
    wire c1 = p1 ^ x0 ^ x2 ^ x3;
    wire c2 = p2 ^ x1 ^ x2 ^ x3;
    wire [2:0] syndrome = {c2, c1, c0};

    assign error_loc = {1'b0, syndrome};

    assign corrected_data = { (syndrome == 3'd3) ? ~x0 : x0,
                              (syndrome == 3'd5) ? ~x1 : x1,
                              (syndrome == 3'd6) ? ~x2 : x2,
                              (syndrome == 3'd7) ? ~x3 : x3 };
endmodule
