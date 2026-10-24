// -----------------------------------------------------------------------------
// Lab 7 - Part 5: Scrolling student number (marquee)
// Two clocks are derived from the 50 MHz board clock:
//   * scan_clk  (2 kHz)   - multiplexes the four digits (as in Part 3)
//   * shift_clk (0.5 Hz)  - shifts a 4-digit window along 403101383
// The window wraps around, so the number scrolls continuously.
//
// Change from the submitted version: the digit selected by state_move = 0
// (leftmost, dig = 1000) now shows the FIRST digit of the window
// (numbers_state[15:12]); previously the window was shown mirrored.
// -----------------------------------------------------------------------------
module scrolling_student_id #(
    parameter integer SHIFT_HALF_PERIOD = 50_000_000, // 0.5 Hz -> one step every 2 s
    parameter integer SCAN_HALF_PERIOD  = 12_500      // 2 kHz digit scan
) (
    input  wire       clk,
    output reg  [3:0] dig,
    output wire       a, b, c, d, e, f, g
);

    wire shift_clk, scan_clk;
    clock_divider #(.HALF_PERIOD(SHIFT_HALF_PERIOD)) u_shift (.clk(clk), .clk_out(shift_clk));
    clock_divider #(.HALF_PERIOD(SCAN_HALF_PERIOD))  u_scan  (.clk(clk), .clk_out(scan_clk));

    reg [3:0]  state_show = 4'd0;     // window position (0..8)
    reg [1:0]  state_move = 2'd0;     // digit being scanned (0..3)
    reg [15:0] numbers_state;         // the 4 digits currently visible
    reg [3:0]  num;

    // 4-digit windows over 4 0 3 1 0 1 3 8 3 (with wrap-around)
    always @(*) begin
        case (state_show)
            4'd0: numbers_state = {4'd4, 4'd0, 4'd3, 4'd1};
            4'd1: numbers_state = {4'd0, 4'd3, 4'd1, 4'd0};
            4'd2: numbers_state = {4'd3, 4'd1, 4'd0, 4'd1};
            4'd3: numbers_state = {4'd1, 4'd0, 4'd1, 4'd3};
            4'd4: numbers_state = {4'd0, 4'd1, 4'd3, 4'd8};
            4'd5: numbers_state = {4'd1, 4'd3, 4'd8, 4'd3};
            4'd6: numbers_state = {4'd3, 4'd8, 4'd3, 4'd4};
            4'd7: numbers_state = {4'd8, 4'd3, 4'd4, 4'd0};
            4'd8: numbers_state = {4'd3, 4'd4, 4'd0, 4'd3};
            default: numbers_state = 16'd0;
        endcase
    end

    // Digit scanning: leftmost digit shows the first digit of the window
    always @(*) begin
        case (state_move)
            2'd0: begin dig = 4'b1000; num = numbers_state[15:12]; end
            2'd1: begin dig = 4'b0100; num = numbers_state[11:8];  end
            2'd2: begin dig = 4'b0010; num = numbers_state[7:4];   end
            2'd3: begin dig = 4'b0001; num = numbers_state[3:0];   end
        endcase
    end

    always @(posedge shift_clk)
        state_show <= (state_show == 4'd8) ? 4'd0 : state_show + 4'd1;

    always @(posedge scan_clk)
        state_move <= state_move + 2'd1;

    Hex_to_7_seg u_dec (
        .Hex(num),
        .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
    );

endmodule
