`timescale 1ns/1ps
module tb_part5;
    reg [3:0] button; wire [4:0] LED; integer i, k, exp, errors = 0;
    part5 dut (.button(button), .LED(LED));
    initial begin
        $dumpfile("tb_part5.vcd"); $dumpvars(0, tb_part5);
        for (i = 0; i < 16; i = i + 1) begin
            button = i; #10; exp = 0;
            for (k = 0; k < 4; k = k + 1) if (!button[k]) exp = k + 1;
            if (LED !== exp) errors = errors + 1;
        end
        $display("RESULT tb_part5: 16/16 combinations (active-low), %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
