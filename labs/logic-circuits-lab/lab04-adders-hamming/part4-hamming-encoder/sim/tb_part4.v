`timescale 1ns/1ps
module tb_part4;
    reg [7:0] Dip = 0; wire [9:0] LED; integer i, errors = 0; reg [6:0] w;
    Part4_module dut (.Dip(Dip), .LED(LED));
    initial begin
        $dumpfile("tb_part4.vcd"); $dumpvars(0, tb_part4);
        for (i = 0; i < 16; i = i + 1) begin
            Dip = i; #10; w = LED[6:0];
            // positions 1..7 = w[6]..w[0]; the three parity checks must all be even
            if ((w[6]^w[4]^w[2]^w[0]) || (w[5]^w[4]^w[1]^w[0]) || (w[3]^w[2]^w[1]^w[0])) errors = errors + 1;
            if ({w[4], w[2], w[1], w[0]} !== Dip[3:0]) errors = errors + 1;   // data bits in place
            $display("  data %b -> code %b", Dip[3:0], w);
        end
        $display("RESULT tb_part4: 16 code words, parity checks and data positions, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
