module scrolling_student_id #(
    parameter integer SHIFT_HALF_PERIOD = 50_000_000,
    parameter integer SCAN_HALF_PERIOD  = 12_500
) (
    input  wire       clk,
    output reg  [3:0] dig,
    output wire       a, b, c, d, e, f, g
);

    wire shift_clk, scan_clk;
    clock_divider #(.HALF_PERIOD(SHIFT_HALF_PERIOD)) u_shift (.clk(clk), .clk_out(shift_clk));
    clock_divider #(.HALF_PERIOD(SCAN_HALF_PERIOD))  u_scan  (.clk(clk), .clk_out(scan_clk));

    reg [3:0]  state_show = 4'd0;
    reg [1:0]  state_move = 2'd0;
    reg [15:0] numbers_state;
    reg [3:0]  num;

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
