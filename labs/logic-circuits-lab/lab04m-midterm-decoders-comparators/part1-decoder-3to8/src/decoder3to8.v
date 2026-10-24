module decoder3to8 (
    input  wire [2:0] numbers,
    output wire [7:0] show
);
    assign show[0] = ~numbers[2] & ~numbers[1] & ~numbers[0];
    assign show[1] = ~numbers[2] & ~numbers[1] &  numbers[0];
    assign show[2] = ~numbers[2] &  numbers[1] & ~numbers[0];
    assign show[3] = ~numbers[2] &  numbers[1] &  numbers[0];
    assign show[4] =  numbers[2] & ~numbers[1] & ~numbers[0];
    assign show[5] =  numbers[2] & ~numbers[1] &  numbers[0];
    assign show[6] =  numbers[2] &  numbers[1] & ~numbers[0];
    assign show[7] =  numbers[2] &  numbers[1] &  numbers[0];
endmodule
