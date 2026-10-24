// -----------------------------------------------------------------------------
// Lab 6 - Part 2: LED "flow" with adjustable speed
// A 10-state sequence first fills the 5 LEDs from the left and then empties
// them from the left:
//   10000 11000 11100 11110 11111 01111 00111 00011 00001 00000
// One step every (max_count + 1) clock cycles - 0.5 s initially.
//   rising edge on button[1] -> step time x2 (slower)
//   rising edge on button[2] -> step time /2 (faster)
// -----------------------------------------------------------------------------
module led_flow #(
    parameter integer INITIAL_STEP = 25_000_000
) (
    input  wire       clk,
    input  wire [3:0] button,
    output reg  [4:0] LED
);
    reg [31:0] max_count = INITIAL_STEP;
    reg [31:0] t         = 32'd0;
    reg        last_b1   = 1'b0;
    reg        last_b2   = 1'b0;
    reg [3:0]  state     = 4'd0;

    // speed control (edge detection on the buttons)
    always @(posedge clk) begin
        last_b1 <= button[1];
        last_b2 <= button[2];
        if (button[1] & ~last_b1)
            max_count <= max_count << 1;
        else if (button[2] & ~last_b2)
            max_count <= max_count >> 1;
    end

    // step timer and state counter
    always @(posedge clk) begin
        if (t >= max_count) begin
            t     <= 32'd0;
            state <= (state == 4'd9) ? 4'd0 : state + 4'd1;
        end else begin
            t     <= t + 32'd1;
        end
    end

    always @(*) begin
        case (state)
            4'd0: LED = 5'b10000;
            4'd1: LED = 5'b11000;
            4'd2: LED = 5'b11100;
            4'd3: LED = 5'b11110;
            4'd4: LED = 5'b11111;
            4'd5: LED = 5'b01111;
            4'd6: LED = 5'b00111;
            4'd7: LED = 5'b00011;
            4'd8: LED = 5'b00001;
            default: LED = 5'b00000;
        endcase
    end
endmodule
