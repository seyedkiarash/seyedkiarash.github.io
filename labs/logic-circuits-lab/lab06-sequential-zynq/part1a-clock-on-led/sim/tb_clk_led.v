`timescale 1ns/1ps
module tb_clk_led;
    reg clk = 0; always #10 clk = ~clk;
    wire [0:0] LED;
    clk_led dut (.clk(clk), .LED(LED));
    integer errors = 0;
    initial begin
        $dumpfile("tb_clk_led.vcd"); $dumpvars(0, tb_clk_led);
        repeat (40) begin #5; if (LED !== clk) errors = errors + 1; end
        $display("RESULT tb_clk_led: LED follows the clock -> %s", errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
