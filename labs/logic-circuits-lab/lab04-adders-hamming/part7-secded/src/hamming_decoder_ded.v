module hamming_decoder_ded (
    input  wire [7:0] received_data,
    output wire [3:0] corrected_data,
    output wire [3:0] error_loc_display,
    output wire       double_error_flag
);
    wire [6:0] r  = received_data[6:0];
    wire p0 = r[6], p1 = r[5], x0 = r[4], p2 = r[3], x1 = r[2], x2 = r[1], x3 = r[0];

    wire [2:0] syndrome = {p2 ^ x1 ^ x2 ^ x3, p1 ^ x0 ^ x2 ^ x3, p0 ^ x0 ^ x1 ^ x3};
    wire       overall  = ^received_data;

    assign double_error_flag = (syndrome != 3'b000) && (overall == 1'b0);

    assign corrected_data = { (syndrome == 3'd3) ? ~x0 : x0,
                              (syndrome == 3'd5) ? ~x1 : x1,
                              (syndrome == 3'd6) ? ~x2 : x2,
                              (syndrome == 3'd7) ? ~x3 : x3 };

    assign error_loc_display = double_error_flag ? 4'hE : {1'b0, syndrome};
endmodule
