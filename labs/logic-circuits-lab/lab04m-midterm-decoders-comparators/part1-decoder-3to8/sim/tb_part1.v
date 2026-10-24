`timescale 1ns/1ps
module tb_part1;
    reg [7:0] Dip = 8'hFF; wire [9:0] LED; integer i, errors = 0;
    part1 dut (.Dip(Dip), .LED(LED));
    initial begin
        $dumpfile("tb_part1.vcd"); $dumpvars(0, tb_part1);
        for (i = 0; i < 256; i = i + 1) begin
            Dip = i; #10;
            if (LED !== (10'b1 << Dip[2:0])) errors = errors + 1;
        end
        $display("RESULT tb_part1: 256 DIP settings, one-hot output checked, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
