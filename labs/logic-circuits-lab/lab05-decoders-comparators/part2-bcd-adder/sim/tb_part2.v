`timescale 1ns/1ps
module tb_part2;
    `include "seg_model.vh"
    reg [7:0] Dip = 8'hFF; wire [3:0] dig; wire a,b,c,d,e,f,g; wire [9:0] LED;
    part2 dut (.Dip(Dip), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .LED(LED));
    integer i, A, B, S, errors = 0; reg [7:0] ch;
    initial begin
        $dumpfile("tb_part2.vcd"); $dumpvars(0, tb_part2);
        for (i = 0; i < 256; i = i + 1) begin
            Dip = i; #10; A = Dip[3:0]; B = Dip[7:4]; ch = char_of({a,b,c,d,e,f,g});
            if (A < 10 && B < 10) begin
                S = A + B;
                if (ch != "0" + S % 10 || LED[0] != (S >= 10) || dig != 4'b0001) errors = errors + 1;
            end else begin
                if (ch != "E" || dig != ((A >= 10 && B >= 10) ? 4'b1001 : 4'b0001)) errors = errors + 1;
            end
        end
        $display("RESULT tb_part2: 100 valid digit pairs + 156 invalid inputs, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
