`timescale 1ns/1ps
module tb_show4dig;
    `include "seg_model.vh"
    reg  [7:0] Dip = 8'hFF;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    show4dig dut (.Dip(Dip), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .dig(dig));
    integer i, errors = 0;
    initial begin
        $dumpfile("tb_show4dig.vcd"); $dumpvars(0, tb_show4dig);
        for (i = 0; i < 256; i = i + 1) begin
            Dip = i; #10;
            if ({a,b,c,d,e,f,g} !== seg_of(Dip[3:0]) || dig !== 4'b1111) begin
                errors = errors + 1;
                $display("FAIL Dip=%h seg=%b", Dip, {a,b,c,d,e,f,g});
            end
        end
        $display("RESULT tb_show4dig: %0d/256 input combinations checked, %0d errors -> %s", 256, errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
