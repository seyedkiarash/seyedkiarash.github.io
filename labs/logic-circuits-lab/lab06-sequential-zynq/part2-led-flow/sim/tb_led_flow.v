`timescale 1ns/1ps
module tb_led_flow;
    reg clk = 0; always #10 clk = ~clk;
    reg [3:0] button = 0;
    wire [4:0] LED;
    led_flow #(.INITIAL_STEP(7)) dut (.clk(clk), .button(button), .LED(LED));

    reg [4:0] expected [0:9];
    integer i, errors = 0; time t0, t1; integer p_base, p_slow, p_fast;
    task step_time(output integer p);
        begin @(dut.state) t0 = $time; @(dut.state) t1 = $time; p = (t1 - t0) / 20; end
    endtask
    task press(input integer k);
        begin @(negedge clk) button[k] = 1; repeat (2) @(negedge clk); button[k] = 0; end
    endtask
    initial begin
        expected[0]=5'b10000; expected[1]=5'b11000; expected[2]=5'b11100; expected[3]=5'b11110; expected[4]=5'b11111;
        expected[5]=5'b01111; expected[6]=5'b00111; expected[7]=5'b00011; expected[8]=5'b00001; expected[9]=5'b00000;
        $dumpfile("tb_led_flow.vcd"); $dumpvars(0, tb_led_flow);
        for (i = 1; i <= 20; i = i + 1) begin
            @(negedge clk); while (dut.state != i % 10) @(negedge clk);
            if (LED !== expected[i % 10]) errors = errors + 1;
        end
        step_time(p_base);
        press(1); step_time(p_slow); step_time(p_slow);
        press(2); press(2); step_time(p_fast); step_time(p_fast);

        $display("  step: %0d cycles, after button1 %0d, after 2x button2 %0d", p_base, p_slow, p_fast);
        $display("RESULT tb_led_flow: 20 steps of the pattern checked, speed control checked -> %s",
                 (errors == 0 && p_base == 8 && p_slow == 15 && p_fast == 4) ? "PASS" : "FAIL");
        $finish;
    end
endmodule
