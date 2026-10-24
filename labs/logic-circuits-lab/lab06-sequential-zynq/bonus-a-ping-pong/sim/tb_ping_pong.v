`timescale 1ns/1ps
module tb_ping_pong;
    reg clk = 0, gameReset = 1;
    reg [3:0] button = 0;
    wire [4:0] LED; wire [3:0] mode, score;
    ping_pong dut (.clk(clk), .gameReset(gameReset), .button(button), .LED(LED), .mode(mode), .score(score));
    task tick; begin #50 clk = 1; #50 clk = 0; end endtask
    integer i, errors = 0;
    initial begin
        $dumpfile("tb_ping_pong.vcd"); $dumpvars(0, tb_ping_pong);
        #20 gameReset = 0;
        // three successful returns
        for (i = 0; i < 3; i = i + 1) begin
            while (LED !== 5'b10000 && LED !== 5'b00001) tick;
            if (LED === 5'b10000) button[3] = 1; else button[0] = 1;
            tick; button = 0;
            tick;                                        // move away from the end
        end
        $display("  after 3 returns: score = %0d", score);
        if (score !== 3) errors = errors + 1;
        while (LED !== 5'b10000 && LED !== 5'b00001) tick;
        tick; tick;                                      // miss: no button pressed
        $display("  after a miss: score = %0d, LED = %b", score, LED);
        if (score !== 0) errors = errors + 1;
        $display("RESULT tb_ping_pong: %s", errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
