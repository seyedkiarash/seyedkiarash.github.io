// -----------------------------------------------------------------------------
// Lab 7 - Part 4: A digit moving across the display
// The character "3" is enabled on one digit at a time; a 0.5 Hz clock moves it
// one position to the right every 2 s (left -> right, then wraps around).
// With a fast clock (as in Part 3) the same circuit would appear to light all
// four digits simultaneously.
// -----------------------------------------------------------------------------
module moving_digit #(
    parameter integer MOVE_HALF_PERIOD = 50_000_000   // 50 MHz / (2*50M) = 0.5 Hz
) (
    input  wire       clk,
    output reg  [3:0] dig,
    output wire       a, b, c, d, e, f, g
);

    wire move_clk;
    clock_divider #(.HALF_PERIOD(MOVE_HALF_PERIOD)) u_div (.clk(clk), .clk_out(move_clk));

    reg [1:0] state = 2'd0;

    always @(*) begin
        case (state)
            2'd0: dig = 4'b1000;
            2'd1: dig = 4'b0100;
            2'd2: dig = 4'b0010;
            2'd3: dig = 4'b0001;
        endcase
    end

    always @(posedge move_clk)
        state <= state + 2'd1;

    Hex_to_7_seg u_dec (
        .Hex(4'd3),
        .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
    );

endmodule
