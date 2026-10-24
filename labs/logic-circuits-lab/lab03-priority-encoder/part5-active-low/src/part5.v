// -----------------------------------------------------------------------------
// Lab 3 - Part 5: Priority encoder with active-low push buttons
// The board's push buttons read 0 when pressed, so they are inverted before
// the encoder (compare with Part 3, where they were used directly).
// -----------------------------------------------------------------------------
module part5 (
    input  wire [3:0] button,
    output wire [4:0] LED
);
    wire [2:0] code;
    encoderpr u_enc (.A(~button), .c(code));

    assign LED[2:0] = code;
    assign LED[4:3] = 2'b00;
endmodule
