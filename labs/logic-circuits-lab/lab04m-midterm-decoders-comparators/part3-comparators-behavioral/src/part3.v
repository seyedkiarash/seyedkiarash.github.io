module part3 (
    input  wire [7:0] Dip,
    output wire [9:0] LED
);
    unsigned_checking    ch1 (.A(Dip[3:0]), .B(Dip[7:4]), .c(LED[0]));
    check_signed_greater ch2 (.A(Dip[3:0]), .B(Dip[7:4]), .c(LED[1]));
    check_signed_equal   ch3 (.A(Dip[3:0]), .B(Dip[7:4]), .c(LED[2]));
    assign LED[9:3] = 7'b0;
endmodule
