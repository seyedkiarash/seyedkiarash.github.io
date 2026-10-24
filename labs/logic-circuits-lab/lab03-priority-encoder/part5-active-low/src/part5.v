module part5 (
    input  wire [3:0] button,
    output wire [4:0] LED
);
    wire [2:0] code;
    encoderpr u_enc (.A(~button), .c(code));

    assign LED[2:0] = code;
    assign LED[4:3] = 2'b00;
endmodule
