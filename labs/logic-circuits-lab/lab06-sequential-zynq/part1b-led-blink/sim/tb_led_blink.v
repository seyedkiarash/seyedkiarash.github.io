`timescale 1ns/1ps
module tb_led_blink;
    reg clk = 0; always #10 clk = ~clk;
    wire [0:0] LED;
    led_blink #(.HALF_PERIOD(10)) dut (.clk(clk), .LED(LED));
    time t_prev = 0; integer n = 0, errors = 0;
    always @(LED) begin
        if (n > 0 && ($time - t_prev) != 200) errors = errors + 1;
        t_prev = $time; n = n + 1;
    end
    initial begin
        $dumpfile("tb_led_blink.vcd"); $dumpvars(0, tb_led_blink);
        #5000;
        $display("RESULT tb_led_blink: %0d toggles, each after exactly HALF_PERIOD cycles -> %s", n, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
