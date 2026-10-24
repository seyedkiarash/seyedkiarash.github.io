module snake_display #(
    parameter integer SCAN_DIV = 25_000,
    parameter integer MOVE_DIV = 12_500_000,
    parameter integer LENGTH   = 3
) (
    input  wire       clk,
    output reg        a, b, c, d, e, f, g,
    output reg  [3:0] dig
);
    reg [31:0] scan_cnt = 0, move_cnt = 0;
    wire scan_tick = (scan_cnt == SCAN_DIV - 1);
    wire move_tick = (move_cnt == MOVE_DIV - 1);

    always @(posedge clk) begin
        scan_cnt <= scan_tick ? 0 : scan_cnt + 1;
        move_cnt <= move_tick ? 0 : move_cnt + 1;
    end

    reg [3:0] head_pos = 4'd0;
    always @(posedge clk)
        if (move_tick)
            head_pos <= (head_pos == 4'd11) ? 4'd0 : head_pos + 4'd1;

    function [8:0] ring;
        input [3:0] p;
        case (p)
            4'd0:  ring = {2'd3, 7'b1000000};
            4'd1:  ring = {2'd2, 7'b1000000};
            4'd2:  ring = {2'd1, 7'b1000000};
            4'd3:  ring = {2'd0, 7'b1000000};
            4'd4:  ring = {2'd0, 7'b0100000};
            4'd5:  ring = {2'd0, 7'b0010000};
            4'd6:  ring = {2'd0, 7'b0001000};
            4'd7:  ring = {2'd1, 7'b0001000};
            4'd8:  ring = {2'd2, 7'b0001000};
            4'd9:  ring = {2'd3, 7'b0001000};
            4'd10: ring = {2'd3, 7'b0000100};
            default: ring = {2'd3, 7'b0000010};
        endcase
    endfunction

    reg [6:0] pattern [0:3];
    reg [8:0] r;
    integer i, k;
    always @(*) begin
        for (i = 0; i < 4; i = i + 1) pattern[i] = 7'b0;
        for (k = 0; k < LENGTH; k = k + 1) begin
            r = ring((head_pos >= k) ? head_pos - k[3:0] : head_pos + 4'd12 - k[3:0]);
            pattern[r[8:7]] = pattern[r[8:7]] | r[6:0];
        end
    end

    reg [1:0] scan_idx = 2'd0;
    always @(posedge clk)
        if (scan_tick) scan_idx <= scan_idx + 2'd1;

    always @(*) begin
        dig             = 4'b0001 << scan_idx;
        {a,b,c,d,e,f,g} = ~pattern[scan_idx];
    end
endmodule
