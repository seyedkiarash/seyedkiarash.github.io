`timescale 1ns/1ps
module tb_stopwatch_start_stop;
    reg clk = 0; always #10 clk = ~clk;
    reg [3:0] button = 0;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    stopwatch_start_stop #(.TICK_HALF_PERIOD(4), .SCAN_HALF_PERIOD(1))
        dut (.clk(clk), .button(button), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .dig(dig));

    function [15:0] value; input dummy; value = {dut.n4, dut.n3, dut.n2, dut.n1}; endfunction
    task press(input integer i, input integer len);
        begin @(negedge clk) button[i] = 1; repeat (len) @(negedge clk); button[i] = 0; end
    endtask
    reg [15:0] v0, v1, v2, v3; integer errors = 0;
    initial begin
        $dumpfile("tb_stopwatch_start_stop.vcd"); $dumpvars(0, tb_stopwatch_start_stop);
        repeat (200) @(negedge clk); v0 = value(0);
        press(2, 3); repeat (400) @(negedge clk); v1 = value(0);
        press(1, 3); repeat (5) @(posedge dut.tick_clk); v2 = value(0);
        repeat (200) @(negedge clk);
        if (value(0) != v2) errors = errors + 1;
        press(3, 20); repeat (3) @(posedge dut.tick_clk); v3 = value(0);
        $display("  power-up %h | after start %h | stopped at %h (held) | after reset %h", v0, v1, v2, v3);
        if (v0 != 0 || v1 == 0 || v3 != 0) errors = errors + 1;
        $display("RESULT tb_stopwatch_start_stop: %s", errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
