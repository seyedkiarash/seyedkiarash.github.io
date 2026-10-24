`timescale 1ns/1ps
module tb_priority_encoder;
    reg [3:0] button; wire [4:0] LED; integer i, k, exp, errors = 0;
    priority_encoder dut (.button(button), .LED(LED));
    initial begin
        $dumpfile("tb_priority_encoder.vcd"); $dumpvars(0, tb_priority_encoder);
        for (i = 0; i < 16; i = i + 1) begin
            button = i; #10; exp = 0;
            for (k = 0; k < 4; k = k + 1) if (button[k]) exp = k + 1;
            if (LED !== exp) errors = errors + 1;
            $display("  button=%b -> LED=%b", button, LED);
        end
        $display("RESULT tb_priority_encoder: 16/16 combinations, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
