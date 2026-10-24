`timescale 1ns/1ps
// After the width fix the outputs must depend on the buttons. The testbench
// counts, over all 256 DIP settings, how many make the outputs respond to the
// buttons, and prints the full truth table for DIP = 0000_0000.
module tb_bonus2;
    reg [7:0] Dip = 8'hFF; reg [3:0] button = 4'hF; wire [9:0] LED;
    integer d, k, responsive = 0; reg [2:0] first; reg varies; reg [3:0] nb;
    bonus2 dut (.button(button), .Dip(Dip), .LED(LED));
    initial begin
        $dumpfile("tb_bonus2.vcd"); $dumpvars(0, tb_bonus2);
        for (d = 0; d < 256; d = d + 1) begin
            varies = 0;
            for (k = 0; k < 16; k = k + 1) begin
                Dip = d; nb = k; button = ~nb; #10;
                if (k == 0) first = LED[2:0]; else if (LED[2:0] !== first) varies = 1;
                if (d == 0) $display("  DIP=00000000 nb(pressed)=%b -> LED[2:0]=%b", nb, LED[2:0]);
            end
            if (varies) responsive = responsive + 1;
        end
        $display("RESULT tb_bonus2: outputs respond to the buttons for %0d of 256 DIP settings -> %s",
                 responsive, (responsive > 0) ? "PASS" : "FAIL");
        $finish;
    end
endmodule
