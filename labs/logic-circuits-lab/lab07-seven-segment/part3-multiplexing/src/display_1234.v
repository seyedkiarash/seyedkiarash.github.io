// -----------------------------------------------------------------------------
// Lab 7 - Part 3: Time-multiplexed display ("1234")
// The four digits share the segment lines, so only one digit is enabled at a
// time. A 2 kHz scan clock rotates through the digits; each digit is lit for
// 0.5 ms and refreshed at 500 Hz, which the eye sees as a steady "1234".
// -----------------------------------------------------------------------------
module display_1234 #(
    parameter integer SCAN_HALF_PERIOD = 12_500       // 50 MHz / (2*12.5k) = 2 kHz
) (
    input  wire       clk,
    output wire       a, b, c, d, e, f, g,
    output reg  [3:0] dig
);

    wire scan_clk;
    clock_divider #(.HALF_PERIOD(SCAN_HALF_PERIOD)) u_div (.clk(clk), .clk_out(scan_clk));

    reg [1:0] state = 2'd0;
    reg [3:0] number;

    always @(*) begin
        case (state)
            2'd0: begin number = 4'd1; dig = 4'b1000; end   // leftmost digit
            2'd1: begin number = 4'd2; dig = 4'b0100; end
            2'd2: begin number = 4'd3; dig = 4'b0010; end
            2'd3: begin number = 4'd4; dig = 4'b0001; end   // rightmost digit
        endcase
    end

    always @(posedge scan_clk)
        state <= state + 2'd1;                        // wraps 3 -> 0

    Hex_to_7_seg u_dec (
        .Hex(number),
        .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
    );

endmodule
