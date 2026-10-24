// -----------------------------------------------------------------------------
// Lab 5 - Bonus 2: logic built only from 8-to-1 multiplexers
// Two multiplexers use the DIP switches as a programmable truth table (f1, f2);
// two more use the constant 1001_0110 - the truth table of a 3-input XOR.
// Outputs: LED[0] = ~f2, LED[1] = ~a1 & ~a2, LED[2] = (a1 | a2) & f2.
//
// Change from the submitted version: the select buses s1 and s2 were declared
// as 1-bit wires (wire s1 = {...}), so only the last bit of each concatenation
// was kept and the circuit synthesised to 3 LUTs that ignored the buttons.
// They are declared [2:0] here. See the lab report for the remaining open
// question about the intended function.
// -----------------------------------------------------------------------------
module bonus2 (
    input  wire [3:0] button,
    input  wire [7:0] Dip,
    output wire [9:0] LED
);
    wire [3:0] nb = ~button;                 // buttons are active-low
    wire       f1, f2, a1, a2;

    wire [2:0] s1 = {nb[2], nb[0], 1'b0};
    wire [2:0] s2 = {nb[3], nb[1], f1};
    multi fa1 (.A(Dip), .s(s1), .f(f1));
    multi fa2 (.A(Dip), .s(s2), .f(f2));

    localparam [7:0] XOR3 = 8'b1001_0110;
    multi xo1 (.A(XOR3), .s({nb[0], nb[1], 1'b0}), .f(a1));
    multi xo2 (.A(XOR3), .s({nb[2], nb[3], f1}),   .f(a2));

    assign LED[0]   = ~f2;
    assign LED[1]   = ~a2 & ~a1;
    assign LED[2]   = (a2 | a1) & f2;
    assign LED[9:3] = 7'b0;
endmodule
