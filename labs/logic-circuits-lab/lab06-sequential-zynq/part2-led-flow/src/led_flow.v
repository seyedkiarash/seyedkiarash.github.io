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

    always @(posedge clk) begin
        last_b1 <= button[1];
        last_b2 <= button[2];
        if (button[1] & ~last_b1)
            max_count <= max_count << 1;
        else if (button[2] & ~last_b2)
            max_count <= max_count >> 1;
    end

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
