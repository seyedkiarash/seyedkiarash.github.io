`timescale 1ns/1ps
module tb_part1;
    `include "seg_model.vh"
    reg [7:0] Dip = 8'hFF; wire [3:0] dig; wire a,b,c,d,e,f,g; integer i, errors = 0;
    Part1_module dut (.Dip(Dip), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g));
    initial begin
        $dumpfile("tb_part1.vcd"); $dumpvars(0, tb_part1);
        for (i = 0; i < 256; i = i + 1) begin
            Dip = i; #10;
            if ({a,b,c,d,e,f,g} !== seg_of(Dip[3:0]) || dig !== 4'b0001) errors = errors + 1;
        end
        $display("RESULT tb_part1: 256 DIP settings, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
