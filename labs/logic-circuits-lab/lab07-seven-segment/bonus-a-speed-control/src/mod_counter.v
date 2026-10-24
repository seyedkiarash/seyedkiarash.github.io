module mod_counter (
    input  wire [3:0] N,
    input  wire       clk,
    input  wire       enable,
    output reg  [3:0] number = 4'd0,
    output wire       done
);

    always @(posedge clk)
        if (enable)
            number <= (number == N) ? 4'd0 : number + 4'd1;

    assign done = enable && (number == N);

endmodule
