`timescale 1ns/1ps
module tb_multiplier;
    reg [7:0] Dip = 8'hFF; wire [9:0] LED; integer i, errors = 0;
    multiplier_comb_top dut (.Dip(Dip), .LED(LED));
    initial begin
        $dumpfile("tb_multiplier.vcd"); $dumpvars(0, tb_multiplier);
        for (i = 0; i < 256; i = i + 1) begin
            Dip = i; #10;
            if (LED[7:0] !== Dip[3:0] * Dip[7:4]) errors = errors + 1;
        end
        $display("RESULT tb_multiplier: all 256 products, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
