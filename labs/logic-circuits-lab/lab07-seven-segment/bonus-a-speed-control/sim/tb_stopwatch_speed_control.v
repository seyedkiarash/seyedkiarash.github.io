`timescale 1ns/1ps
// Measures the tick period before and after pressing the speed buttons.
module tb_stopwatch_speed_control;
    reg clk = 0; always #10 clk = ~clk;
    reg [3:0] button = 0;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    stopwatch_speed_control #(.INITIAL_HALF_PERIOD(8), .SCAN_HALF_PERIOD(1))
        dut (.clk(clk), .button(button), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .dig(dig));

    time t0, t1; integer p_base, p_slow, p_fast, errors = 0;
    task measure(output integer p);
        begin @(posedge dut.tick_clk) t0 = $time; @(posedge dut.tick_clk) t1 = $time; p = (t1 - t0) / 20; end
    endtask
    task press(input integer i);
        begin @(negedge clk) button[i] = 1; repeat (3) @(negedge clk); button[i] = 0; end
    endtask

    initial begin
        $dumpfile("tb_stopwatch_speed_control.vcd"); $dumpvars(0, tb_stopwatch_speed_control);
        measure(p_base);
        press(1); repeat (2) measure(p_slow);         // button 1: slower
        press(2); press(2); repeat (2) measure(p_fast);  // button 2 twice: x0.25
        $display("  tick period: initial %0d cycles, after button1 %0d, after 2x button2 %0d", p_base, p_slow, p_fast);
        if (p_slow != 2*p_base) errors = errors + 1;
        if (p_fast != p_base/2) errors = errors + 1;
        $display("RESULT tb_stopwatch_speed_control: %s", errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
