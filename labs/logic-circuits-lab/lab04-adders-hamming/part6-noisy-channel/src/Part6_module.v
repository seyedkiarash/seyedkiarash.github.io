// -----------------------------------------------------------------------------
// Lab 4 - Part 6: Encoder -> noisy channel -> decoder
//   data  = DIP[4:1]
//   noise = {DIP[5], DIP[6], DIP[7], ~button[0], ~button[1], ~button[2], ~button[3]}
//           (buttons are active-low; each '1' flips one bit of the code word)
// The decoded (corrected) data is shown on LED[4:1] and the detected error
// position on the 7-segment display.
// -----------------------------------------------------------------------------
module Part6_module (
    input  wire [7:0] Dip,
    input  wire [3:0] button,
    output wire [9:0] LED,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g
);
    wire [6:0] encoded, received;
    wire [3:0] data, err;
    wire [6:0] noise = {Dip[5], Dip[6], Dip[7], ~button[0], ~button[1], ~button[2], ~button[3]};

    hamming_encoder   U_Enc  (.data_in(Dip[4:1]), .encoded_data(encoded));
    transmission_line U_Line (.data_in(encoded), .noise_in(noise), .data_out(received));
    hamming_decoder   U_Dec  (.received_data(received), .corrected_data(data), .error_loc(err));
    Hex_to_7_seg      U_Hex  (.Hex(err), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

    assign LED[4:1] = data;
    assign LED[0]   = 1'b0;
    assign LED[9:5] = 5'b0;
    assign dig      = 4'b0001;
endmodule
