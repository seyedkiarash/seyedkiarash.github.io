`timescale 1ns/1ps
module tb_part2;
    `include "seg_model.vh"
    reg [7:0] Dip = 8'hFF; wire [3:0] dig; wire a,b,c,d,e,f,g; integer i, sum, errors = 0;
    Part2_module dut (.Dip(Dip), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g));
    initial begin
        $dumpfile("tb_part2.vcd"); $dumpvars(0, tb_part2);
        for (i = 0; i < 256; i = i + 1) begin
            Dip = i; #10;
            sum = Dip[3:1] + Dip[6:4] + Dip[7];
            if ({a,b,c,d,e,f,g} !== seg_of(sum)) errors = errors + 1;
        end
        $display("RESULT tb_part2: all 256 (A,B,Cin) combinations, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
