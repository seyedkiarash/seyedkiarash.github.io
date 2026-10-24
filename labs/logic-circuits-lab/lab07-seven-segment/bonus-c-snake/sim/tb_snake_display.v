`timescale 1ns/1ps
// Records one 12-step loop of the snake. For every step the testbench
// reconstructs which segments are lit on each digit and prints a frame line;
// the frames are also used to draw the figure in the report.
module tb_snake_display;
    reg clk = 0; always #10 clk = ~clk;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    snake_display #(.SCAN_BIT(1), .MOVE_BIT(7), .DIGIT_ACTIVE_LOW(1))
        dut (.clk(clk), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .dig(dig));
    reg [6:0] lit [3:0]; integer k, step, nlit, errors = 0;
    initial begin
        $dumpfile("tb_snake_display.vcd"); $dumpvars(0, tb_snake_display);
        for (step = 0; step < 12; step = step + 1) begin
            @(posedge dut.move_clk); repeat (4) @(negedge clk);
            for (k = 0; k < 4; k = k + 1) lit[k] = 0;
            repeat (16) begin
                @(negedge clk);
                for (k = 0; k < 4; k = k + 1) if (~dig == (4'b0001 << k)) lit[k] = ~{a,b,c,d,e,f,g};
            end
            nlit = $countones({lit[3], lit[2], lit[1], lit[0]});
            if (nlit != 3) errors = errors + 1;
            $display("FRAME head=%0d d3=%b d2=%b d1=%b d0=%b", dut.head_pos, lit[3], lit[2], lit[1], lit[0]);
        end
        $display("RESULT tb_snake_display: 12 steps, every frame has exactly 3 lit segments: %s", errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
