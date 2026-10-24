`timescale 1ns/1ps
module tb_part4;
    reg [7:0] Dip = 0; reg [3:0] button = 4'hF; wire [4:0] LED; integer i, s, errors = 0;
    part4 dut (.Dip(Dip), .button(button), .LED(LED));
    initial begin
        $dumpfile("tb_part4.vcd"); $dumpvars(0, tb_part4);
        for (i = 0; i < 256; i = i + 1)
            for (s = 0; s < 8; s = s + 1) begin
                Dip = i; button = {1'b1, ~s[2:0]}; #10;
                if (LED[0] !== Dip[s]) errors = errors + 1;
            end
        $display("RESULT tb_part4: 256 data words x 8 select codes, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
