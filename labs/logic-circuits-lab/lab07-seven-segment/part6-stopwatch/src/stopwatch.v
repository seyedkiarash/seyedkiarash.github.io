// -----------------------------------------------------------------------------
// Lab 7 - Part 6: Stopwatch  (M SS.d  ->  0.0 s ... 9 min 59.9 s)
//
//   tick_clk (10 Hz) -> c1 (tenths, mod 10) -> c2 (seconds, mod 10)
//                    -> c3 (tens of seconds, mod 6) -> c4 (minutes, mod 10)
//
// The counters are cascaded synchronously: each one is enabled by the done
// (carry) output of the previous one. A 2 kHz scan clock multiplexes the four
// digits; c1 is shown on the rightmost digit and c4 on the leftmost.
// -----------------------------------------------------------------------------
module stopwatch #(
    parameter integer TICK_HALF_PERIOD = 2_500_000,   // 50 MHz / (2*2.5M) = 10 Hz
    parameter integer SCAN_HALF_PERIOD = 12_500       // 2 kHz
) (
    input  wire       clk,
    output wire       a, b, c, d, e, f, g,
    output reg  [3:0] dig
);

    wire tick_clk, scan_clk;
    clock_divider #(.HALF_PERIOD(TICK_HALF_PERIOD)) u_tick (.clk(clk), .clk_out(tick_clk));
    clock_divider #(.HALF_PERIOD(SCAN_HALF_PERIOD)) u_scan (.clk(clk), .clk_out(scan_clk));

    wire [3:0] n1, n2, n3, n4;
    wire       e2, e3, e4, e5;

    mod_counter c1 (.N(4'd9), .clk(tick_clk), .enable(1'b1), .number(n1), .done(e2));
    mod_counter c2 (.N(4'd9), .clk(tick_clk), .enable(e2),   .number(n2), .done(e3));
    mod_counter c3 (.N(4'd5), .clk(tick_clk), .enable(e3),   .number(n3), .done(e4));
    mod_counter c4 (.N(4'd9), .clk(tick_clk), .enable(e4),   .number(n4), .done(e5));

    // Display multiplexing
    reg [1:0] state = 2'd0;
    reg [3:0] num;

    always @(*) begin
        case (state)
            2'd0: begin num = n1; dig = 4'b0001; end   // tenths   (rightmost)
            2'd1: begin num = n2; dig = 4'b0010; end   // seconds
            2'd2: begin num = n3; dig = 4'b0100; end   // tens of seconds
            2'd3: begin num = n4; dig = 4'b1000; end   // minutes  (leftmost)
        endcase
    end

    always @(posedge scan_clk)
        state <= state + 2'd1;

    Hex_to_7_seg u_dec (
        .Hex(num),
        .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
    );

endmodule
