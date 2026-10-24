module stopwatch_speed_control #(
    parameter integer INITIAL_HALF_PERIOD = 5_000_000,
    parameter integer SCAN_HALF_PERIOD    = 12_500
) (
    input  wire       clk,
    input  wire [3:0] button,
    output wire       a, b, c, d, e, f, g,
    output reg  [3:0] dig
);

    wire tick_clk, scan_clk;
    variable_clock_divider #(.INITIAL_HALF_PERIOD(INITIAL_HALF_PERIOD))
        u_tick (.clk(clk), .button(button), .clk_out(tick_clk));
    clock_divider #(.HALF_PERIOD(SCAN_HALF_PERIOD)) u_scan (.clk(clk), .clk_out(scan_clk));

    wire [3:0] n1, n2, n3, n4;
    wire       e2, e3, e4, e5;

    mod_counter c1 (.N(4'd9), .clk(tick_clk), .enable(1'b1), .number(n1), .done(e2));
    mod_counter c2 (.N(4'd9), .clk(tick_clk), .enable(e2),   .number(n2), .done(e3));
    mod_counter c3 (.N(4'd5), .clk(tick_clk), .enable(e3),   .number(n3), .done(e4));
    mod_counter c4 (.N(4'd9), .clk(tick_clk), .enable(e4),   .number(n4), .done(e5));

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
