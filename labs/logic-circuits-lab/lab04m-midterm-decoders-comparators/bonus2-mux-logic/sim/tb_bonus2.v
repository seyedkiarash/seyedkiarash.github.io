`timescale 1ns/1ps
module tb_bonus2;
    reg  [7:0] Dip = 8'h00;
    reg  [3:0] button = 4'hF;
    wire [9:0] LED;
    integer d, k, X, Y, errors = 0;
    reg [3:0] nb;
    bonus2 dut (.button(button), .Dip(Dip), .LED(LED));
    initial begin
        $dumpfile("tb_bonus2.vcd"); $dumpvars(0, tb_bonus2);
        for (d = 0; d < 256; d = d + 16)
            for (k = 0; k < 16; k = k + 1) begin
                Dip = d; nb = k; button = ~nb; #10;
                X = {nb[2], nb[0]}; Y = {nb[3], nb[1]};
                if (LED[0] !== (X >= Y) || LED[1] !== (X == Y) || LED[2] !== (X < Y)) errors = errors + 1;
            end
        $display("RESULT tb_bonus2: 2-bit comparator, all 16 operand pairs (x16 DIP settings), %0d errors -> %s",
                 errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
