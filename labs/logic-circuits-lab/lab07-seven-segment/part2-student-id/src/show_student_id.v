module show_student_id #(
    parameter integer STEP_HALF_PERIOD = 12_500_000
) (
    input  wire       clk,
    output wire       a, b, c, d, e, f, g,
    output wire [3:0] dig
);

    assign dig = 4'b1111;

    wire step_clk;
    clock_divider #(.HALF_PERIOD(STEP_HALF_PERIOD)) u_div (.clk(clk), .clk_out(step_clk));

    reg [3:0] state = 4'd0;
    reg [3:0] number;

    always @(*) begin
        case (state)
            4'd0: number = 4'd4;
            4'd1: number = 4'd0;
            4'd2: number = 4'd3;
            4'd3: number = 4'd1;
            4'd4: number = 4'd0;
            4'd5: number = 4'd1;
            4'd6: number = 4'd3;
            4'd7: number = 4'd8;
            4'd8: number = 4'd3;
            default: number = 4'd0;
        endcase
    end

    always @(posedge step_clk)
        state <= (state == 4'd9) ? 4'd0 : state + 4'd1;

    Hex_to_7_seg u_dec (
        .Hex(number),
        .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
    );

endmodule
