module ping_pong (
    input  wire       clk,
    input  wire       gameReset,
    input  wire [3:0] button,
    output reg  [4:0] LED,
    output wire [3:0] mode,
    output wire [3:0] score
);
    reg [3:0] level     = 4'd0;
    reg [2:0] pos       = 3'd0;
    reg       direction = 1'b0;
    reg       last_b0   = 1'b0;
    reg       last_b3   = 1'b0;

    always @(posedge clk or posedge gameReset) begin
        if (gameReset) begin
            level <= 4'd0; pos <= 3'd0; direction <= 1'b0;
            last_b0 <= 1'b0; last_b3 <= 1'b0;
        end else begin
            last_b0 <= button[0];
            last_b3 <= button[3];
            if (direction == 1'b0) begin
                if (pos < 3'd4)
                    pos <= pos + 3'd1;
                else if (button[3] && !last_b3) begin
                    if (level < 4'd9) level <= level + 4'd1;
                    direction <= 1'b1;
                    pos       <= 3'd3;
                end else begin
                    level <= 4'd0; pos <= 3'd0; direction <= 1'b0;
                end
            end else begin
                if (pos > 3'd0)
                    pos <= pos - 3'd1;
                else if (button[0] && !last_b0) begin
                    if (level < 4'd9) level <= level + 4'd1;
                    direction <= 1'b0;
                    pos       <= 3'd1;
                end else begin
                    level <= 4'd0; pos <= 3'd0; direction <= 1'b0;
                end
            end
        end
    end

    always @(*) LED = 5'b00001 << pos;

    assign mode  = level;
    assign score = level;
endmodule
