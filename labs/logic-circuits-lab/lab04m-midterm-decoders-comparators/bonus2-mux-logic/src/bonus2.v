module bonus2 (
    input  wire [3:0] button,
    input  wire [7:0] Dip,
    output wire [9:0] LED
);
    localparam [7:0] XOR3   = 8'b1001_0110;
    localparam [7:0] BORROW = 8'b1000_1110;

    wire [3:0] nb = ~button;
    wire x0 = nb[0], y0 = nb[1], x1 = nb[2], y1 = nb[3];
    wire b0, b1, d0, d1;

    multi m_b0 (.A(BORROW), .s({x0, y0, 1'b0}), .f(b0));
    multi m_b1 (.A(BORROW), .s({x1, y1, b0}),   .f(b1));
    multi m_d0 (.A(XOR3),   .s({x0, y0, 1'b0}), .f(d0));
    multi m_d1 (.A(XOR3),   .s({x1, y1, b0}),   .f(d1));

    wire equal = ~d0 & ~d1;

    assign LED[0]   = ~b1;
    assign LED[1]   = equal;
    assign LED[2]   = b1;
    assign LED[9:3] = 7'b0;
endmodule
