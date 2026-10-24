module mod_counter_reset (
    input  wire [3:0] N,
    input  wire       clk,
    input  wire       enable,
    input  wire [3:0] button,
    output reg  [3:0] number = 4'd0,
    output wire       done
);

    reg last_b3 = 1'b0;

    always @(posedge clk) begin
        last_b3 <= button[3];
        if (button[3] & ~last_b3)
            number <= 4'd0;
        else if (enable)
            number <= (number == N) ? 4'd0 : number + 4'd1;
    end

    assign done = enable && (number == N);

endmodule
