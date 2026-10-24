// -----------------------------------------------------------------------------
// Lab 4 - Part 5: Hamming(7,4) decoder
// A received code word is set on DIP[7:1]; the corrected data appears on
// LED[3:0] and the error position (syndrome) on the 7-segment display.
// -----------------------------------------------------------------------------
module Part5_module (
    input  wire [7:0] Dip,
    output wire [9:0] LED,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g
);
    wire [3:0] data, err;

    hamming_decoder U_Dec (.received_data(Dip[7:1]), .corrected_data(data), .error_loc(err));
    Hex_to_7_seg    U_Hex (.Hex(err), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

    assign LED[3:0] = data;
    assign LED[9:4] = 6'b0;
    assign dig      = 4'b0001;
endmodule
