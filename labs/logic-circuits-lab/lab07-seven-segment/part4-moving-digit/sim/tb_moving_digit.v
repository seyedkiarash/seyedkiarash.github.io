`timescale 1ns/1ps
module tb_moving_digit;
    `include "seg_model.vh"
    reg clk = 0; always #10 clk = ~clk;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    moving_digit #(.MOVE_HALF_PERIOD(4)) dut (.clk(clk), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g));
    reg [3:0] last = 4'bx; integer moves = 0, errors = 0;
    initial begin
        $dumpfile("tb_moving_digit.vcd"); $dumpvars(0, tb_moving_digit);
        repeat (200) begin
            @(negedge clk);
            if (char_of({a,b,c,d,e,f,g}) != "3") errors = errors + 1;
            if (dig !== last) begin
                if (last !== 4'bx && dig !== ((last == 4'b0001) ? 4'b1000 : last >> 1)) errors = errors + 1;
                last = dig; moves = moves + 1;
            end
        end
        $display("RESULT tb_moving_digit: %0d position changes observed, %0d errors -> %s", moves, errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
