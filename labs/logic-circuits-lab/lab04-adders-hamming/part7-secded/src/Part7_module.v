// -----------------------------------------------------------------------------
// Lab 4 - Part 7: SECDED channel demo
//   data  = DIP[4:1]
//   noise = {DIP[0], DIP[7], DIP[6], DIP[5], ~button[3], ~button[2], ~button[1], ~button[0]}
// Single errors are corrected (data on LED[4:1], position on the display);
// a double error shows "EE" on two digits and lights LED[4:1] = 1111.
// -----------------------------------------------------------------------------
module Part7_module (
    input  wire [7:0] Dip,
    input  wire [3:0] button,
    output wire [9:0] LED,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g
);
    wire [7:0] encoded, received;
    wire [3:0] data, err_code;
    wire       double_err;
    wire [7:0] noise = {Dip[0], Dip[7], Dip[6], Dip[5], ~button[3], ~button[2], ~button[1], ~button[0]};

    hamming_encoder_ded U_Enc  (.data_in(Dip[4:1]), .encoded_data(encoded));
    transmission_line #(.W(8)) U_Line (.data_in(encoded), .noise_in(noise), .data_out(received));
    hamming_decoder_ded U_Dec  (.received_data(received), .corrected_data(data),
                                .error_loc_display(err_code), .double_error_flag(double_err));
    Hex_to_7_seg        U_Hex  (.Hex(err_code), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

    assign dig      = double_err ? 4'b0011 : 4'b0001;
    assign LED[4:1] = double_err ? 4'b1111 : data;
    assign LED[0]   = 1'b0;
    assign LED[9:5] = 5'b0;
endmodule
