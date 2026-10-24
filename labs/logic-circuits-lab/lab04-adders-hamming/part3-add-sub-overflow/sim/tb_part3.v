`timescale 1ns/1ps
module tb_part3;
    `include "seg_model.vh"
    reg [7:0] Dip = 8'hFF; reg [1:0] pb = 0;
    wire [3:0] dig; wire a,b,c,d,e,f,g; wire [9:0] LED;
    Part3_module dut (.Dip(Dip), .Push_button(pb), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .LED(LED));
    integer i, op, r, errors = 0, ovf = 0; reg signed [3:0] A, B;
    initial begin
        $dumpfile("tb_part3.vcd"); $dumpvars(0, tb_part3);
        for (op = 0; op < 2; op = op + 1)
            for (i = 0; i < 256; i = i + 1) begin
                Dip = i; pb = {op[0], 1'b0}; #10;
                A = Dip[7:4]; B = Dip[3:0];
                r = op ? A - B : A + B;
                if (r > 7 || r < -8) begin
                    ovf = ovf + 1;
                    if (LED[0] !== 1'b1 || dig !== 4'b0000) errors = errors + 1;
                end else begin
                    if (LED[0] !== 1'b0 || dig !== 4'b0001) errors = errors + 1;
                    if (LED[9] !== (r < 0)) errors = errors + 1;
                    if ({a,b,c,d,e,f,g} !== seg_of(r < 0 ? -r : r)) errors = errors + 1;
                end
            end
        $display("RESULT tb_part3: 512 cases (256 x add/sub), %0d overflow cases flagged, %0d errors -> %s",
                 ovf, errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
