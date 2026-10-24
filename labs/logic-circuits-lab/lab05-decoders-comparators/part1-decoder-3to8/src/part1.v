// Lab 5 - Part 1: 3-to-8 decoder, DIP[2:0] -> one of LED[7:0]
module part1 (
    input  wire [7:0] Dip,
    output wire [9:0] LED
);
    decoder3to8 u_dec (.numbers(Dip[2:0]), .show(LED[7:0]));
    assign LED[9:8] = 2'b00;
endmodule
