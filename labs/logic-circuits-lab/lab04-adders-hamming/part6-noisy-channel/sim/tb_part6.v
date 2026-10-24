`timescale 1ns/1ps

module tb_part6;
    reg [7:0] Dip = 0; reg [3:0] button = 4'b1111;
    wire [9:0] LED; wire [3:0] dig; wire a,b,c,d,e,f,g;
    Part6_module dut (.Dip(Dip), .button(button), .LED(LED), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g));
    integer dw, n, errors = 0, single = 0, dbl = 0, dbl_wrong = 0;
    reg [6:0] noise;
    initial begin
        $dumpfile("tb_part6.vcd"); $dumpvars(0, tb_part6);
        for (dw = 0; dw < 16; dw = dw + 1)
            for (n = 0; n < 128; n = n + 1) begin
                noise = n;
                if ($countones(noise) <= 2) begin
                    Dip = {noise[4], noise[5], noise[6], dw[3:0], 1'b0};
                    button = ~{noise[0], noise[1], noise[2], noise[3]};
                    #10;
                    if ($countones(noise) <= 1) begin
                        single = single + 1;
                        if (LED[4:1] !== dw[3:0]) errors = errors + 1;
                    end else begin
                        dbl = dbl + 1;
                        if (LED[4:1] !== dw[3:0]) dbl_wrong = dbl_wrong + 1;
                    end
                end
            end
        $display("  %0d cases with 0/1 errors (must be corrected), %0d double-error cases: %0d decoded wrongly (expected for Hamming(7,4))",
                 single, dbl, dbl_wrong);
        $display("RESULT tb_part6: %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
