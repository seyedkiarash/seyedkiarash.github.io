`timescale 1ns/1ps
module tb_part7;
    reg [7:0] Dip = 0; reg [3:0] button = 4'b1111;
    wire [9:0] LED; wire [3:0] dig; wire a,b,c,d,e,f,g;
    Part7_module dut (.Dip(Dip), .button(button), .LED(LED), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g));
    integer dw, n, errors = 0, s = 0, dbl = 0;
    reg [7:0] noise;
    initial begin
        $dumpfile("tb_part7.vcd"); $dumpvars(0, tb_part7);
        for (dw = 0; dw < 16; dw = dw + 1)
            for (n = 0; n < 256; n = n + 1) begin
                noise = n;
                if ($countones(noise) <= 2) begin

                    Dip = {noise[4], noise[5], noise[6], dw[3:0], noise[7]};
                    button = ~noise[3:0];
                    #10;
                    if ($countones(noise) <= 1) begin
                        s = s + 1;
                        if (LED[4:1] !== dw[3:0] || dut.double_err) errors = errors + 1;
                    end else begin
                        dbl = dbl + 1;
                        if (!dut.double_err || dig !== 4'b0011) errors = errors + 1;
                    end
                end
            end
        $display("  %0d cases with 0/1 errors corrected, %0d double-error cases all detected", s, dbl);
        $display("RESULT tb_part7: %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
