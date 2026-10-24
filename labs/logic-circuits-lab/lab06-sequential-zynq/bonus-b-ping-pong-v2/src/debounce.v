module debounce #(
    parameter integer STABLE = 500_000
) (
    input  wire clk,
    input  wire in,
    output reg  level = 1'b0,
    output wire press
);
    reg s0 = 1'b0, s1 = 1'b0, prev = 1'b0;
    reg [31:0] cnt = 0;

    always @(posedge clk) begin
        s0 <= in;
        s1 <= s0;
        if (s1 == level)
            cnt <= 0;
        else if (cnt == STABLE - 1) begin
            level <= s1;
            cnt   <= 0;
        end else
            cnt <= cnt + 1;
        prev <= level;
    end

    assign press = level & ~prev;
endmodule
