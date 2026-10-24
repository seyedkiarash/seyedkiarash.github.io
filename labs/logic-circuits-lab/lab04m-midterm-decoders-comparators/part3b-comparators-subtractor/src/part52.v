module part52 (
    input  wire [7:0] Dip,
    output wire [9:0] LED
);
    wire z, c, n, v;
    sicom u_cmp (.A(Dip[3:0]), .B(Dip[7:4]), .z(z), .Cout(c), .N(n), .V(v));

    assign LED[0]   = c & ~z;
    assign LED[1]   = ~z & ~(n ^ v);
    assign LED[2]   = z;
    assign LED[9:3] = 7'b0;
endmodule
