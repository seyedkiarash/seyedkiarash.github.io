module ping_pong_v2_top #(
    parameter integer STEP_UNIT         = 1_250_000,
    parameter integer DEBOUNCE          = 500_000,
    parameter         BUTTON_ACTIVE_LOW = 1
) (
    input  wire       in_clk,
    input  wire       gameReset,
    input  wire [3:0] button,
    output wire [4:0] LED,
    output wire [3:0] dig,
    output wire       a, b, c, d, e, f, g, dp
);
    wire [3:0] pressed = BUTTON_ACTIVE_LOW ? ~button : button;
    wire       left, right, rst_level, rst_press;

    debounce #(.STABLE(DEBOUNCE)) u_db_l (.clk(in_clk), .in(pressed[0]), .level(), .press(left));
    debounce #(.STABLE(DEBOUNCE)) u_db_r (.clk(in_clk), .in(pressed[3]), .level(), .press(right));

    reg r0 = 1'b0, r1 = 1'b0;
    always @(posedge in_clk) begin
        r0 <= gameReset;
        r1 <= r0;
    end

    wire [3:0] level;
    wire       win;

    game_logic #(.STEP_UNIT(STEP_UNIT)) u_game (
        .clk(in_clk), .reset(r1), .press_left(left), .press_right(right),
        .leds(LED), .level(level), .win(win)
    );

    Hex_to_7_seg u_dec (.Hex(level), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g));

    assign dig = 4'b0001;
    assign dp  = 1'b1;
endmodule
