`timescale 1ns/1ps
module tb_part52;
    reg [7:0] Dip = 8'hFF; wire [9:0] LED; integer i, errors = 0;
    reg signed [3:0] sa, sb;
    part52 dut (.Dip(Dip), .LED(LED));
    initial begin
        $dumpfile("tb_part52.vcd"); $dumpvars(0, tb_part52);
        for (i = 0; i < 256; i = i + 1) begin
            Dip = i; #10; sa = Dip[3:0]; sb = Dip[7:4];
            if (LED[0] !== (Dip[3:0] > Dip[7:4]) || LED[1] !== (sa > sb) || LED[2] !== (Dip[3:0] == Dip[7:4]))
                errors = errors + 1;
        end
        $display("RESULT tb_part52: 256 (A,B) pairs x 3 outputs, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
