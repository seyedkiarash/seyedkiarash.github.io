module game_logic #(
    parameter integer STEP_UNIT = 1_250_000
) (
    input  wire       clk,
    input  wire       reset,
    input  wire       press_left,
    input  wire       press_right,
    output reg  [4:0] leds,
    output reg  [3:0] level,
    output reg        win
);
    reg [2:0]  pos       = 3'd0;
    reg        dir       = 1'b0;
    reg        returned  = 1'b0;
    reg [31:0] t         = 0;
    reg [31:0] blink     = 0;

    function [4:0] units;
        input [3:0] l;
        case (l)
            4'd0: units = 5'd20;
            4'd1: units = 5'd17;
            4'd2: units = 5'd14;
            4'd3: units = 5'd12;
            4'd4: units = 5'd10;
            4'd5: units = 5'd9;
            4'd6: units = 5'd8;
            4'd7: units = 5'd7;
            4'd8: units = 5'd6;
            default: units = 5'd5;
        endcase
    endfunction

    wire [31:0] step_len = units(level) * STEP_UNIT;
    wire        tick     = (t >= step_len - 1);
    wire        at_end   = (dir == 1'b0 && pos == 3'd4) || (dir == 1'b1 && pos == 3'd0);
    wire        hit      = (dir == 1'b0) ? press_right : press_left;

    always @(posedge clk) begin
        if (reset) begin
            pos <= 3'd0; dir <= 1'b0; level <= 4'd0; win <= 1'b0;
            returned <= 1'b0; t <= 0; blink <= 0;
        end else if (win) begin
            blink <= blink + 1;
            if (press_left | press_right) begin
                pos <= 3'd0; dir <= 1'b0; level <= 4'd0; win <= 1'b0;
                returned <= 1'b0; t <= 0;
            end
        end else begin
            if (at_end && hit) returned <= 1'b1;
            if (tick) begin
                t <= 0;
                if (at_end) begin
                    if (returned || hit) begin
                        returned <= 1'b0;
                        if (level == 4'd8) begin
                            level <= 4'd9;
                            win   <= 1'b1;
                        end else begin
                            level <= level + 4'd1;
                            dir   <= ~dir;
                            pos   <= dir ? 3'd1 : 3'd3;
                        end
                    end else begin
                        level <= 4'd0;
                        dir   <= 1'b0;
                        pos   <= 3'd0;
                    end
                end else begin
                    pos <= dir ? pos - 3'd1 : pos + 3'd1;
                end
            end else begin
                t <= t + 1;
            end
        end
    end

    always @(*) begin
        if (win)
            leds = blink[24] ? 5'b11111 : 5'b00000;
        else
            leds = 5'b00001 << pos;
    end
endmodule
