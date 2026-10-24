// -----------------------------------------------------------------------------
// Lab 7 - Bonus B: Stopwatch with Stop / Start / Reset
//   button[1]  stop   (clears the enable of the first counter)
//   button[2]  start  (sets it again)
//   button[3]  reset  (clears all four counters)
// The stopwatch powers up stopped. Tick rate: 5 Hz (half-period 5,000,000).
// -----------------------------------------------------------------------------
module stopwatch_start_stop #(
    parameter integer TICK_HALF_PERIOD = 5_000_000,
    parameter integer SCAN_HALF_PERIOD = 12_500
) (
    input  wire       clk,
    input  wire [3:0] button,
    output wire       a, b, c, d, e, f, g,
    output reg  [3:0] dig
);

    // Run/stop flag, edge-triggered from the buttons in the 50 MHz domain
    reg run     = 1'b0;
    reg last_b1 = 1'b0;
    reg last_b2 = 1'b0;

    always @(posedge clk) begin
        last_b1 <= button[1];
        last_b2 <= button[2];
        if (button[1] & ~last_b1)
            run <= 1'b0;
        else if (button[2] & ~last_b2)
            run <= 1'b1;
    end

    wire tick_clk, scan_clk;
    clock_divider #(.HALF_PERIOD(TICK_HALF_PERIOD)) u_tick (.clk(clk), .clk_out(tick_clk));
    clock_divider #(.HALF_PERIOD(SCAN_HALF_PERIOD)) u_scan (.clk(clk), .clk_out(scan_clk));

    wire [3:0] n1, n2, n3, n4;
    wire       e2, e3, e4, e5;

    mod_counter_reset c1 (.N(4'd9), .clk(tick_clk), .enable(run), .button(button), .number(n1), .done(e2));
    mod_counter_reset c2 (.N(4'd9), .clk(tick_clk), .enable(e2),  .button(button), .number(n2), .done(e3));
    mod_counter_reset c3 (.N(4'd5), .clk(tick_clk), .enable(e3),  .button(button), .number(n3), .done(e4));
    mod_counter_reset c4 (.N(4'd9), .clk(tick_clk), .enable(e4),  .button(button), .number(n4), .done(e5));

    reg [1:0] state = 2'd0;
    reg [3:0] num;

    always @(*) begin
        case (state)
            2'd0: begin num = n1; dig = 4'b0001; end
            2'd1: begin num = n2; dig = 4'b0010; end
            2'd2: begin num = n3; dig = 4'b0100; end
            2'd3: begin num = n4; dig = 4'b1000; end
        endcase
    end

    always @(posedge scan_clk)
        state <= state + 2'd1;

    Hex_to_7_seg u_dec (
        .Hex(num),
        .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
    );

endmodule
