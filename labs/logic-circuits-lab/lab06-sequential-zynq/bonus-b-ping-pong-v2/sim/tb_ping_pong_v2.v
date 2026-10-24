`timescale 1ns/1ps
module tb_ping_pong_v2;
    reg clk = 0; always #10 clk = ~clk;
    reg gameReset = 1;
    reg [3:0] button = 4'hF;
    wire [4:0] LED; wire [3:0] dig; wire a,b,c,d,e,f,g,dp;

    ping_pong_v2_top #(.STEP_UNIT(4), .DEBOUNCE(3), .BUTTON_ACTIVE_LOW(1)) dut (
        .in_clk(clk), .gameReset(gameReset), .button(button), .LED(LED), .dig(dig),
        .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g),.dp(dp));

    task press(input integer k);
        begin
            button[k] = 1'b0; repeat (8) @(negedge clk);
            button[k] = 1'b1; repeat (8) @(negedge clk);
        end
    endtask

    task wait_end;
        begin
            while (!dut.u_game.at_end) @(negedge clk);
        end
    endtask

    integer i, errors = 0, lvl_before;
    initial begin
        $dumpfile("tb_ping_pong_v2.vcd"); $dumpvars(0, tb_ping_pong_v2);
        repeat (5) @(negedge clk); gameReset = 0;

        for (i = 0; i < 3; i = i + 1) begin
            wait_end;
            press(dut.u_game.dir ? 0 : 3);
            while (dut.u_game.at_end) @(negedge clk);
        end
        $display("  after 3 returns: level = %0d", dut.level);
        if (dut.level != 3) errors = errors + 1;

        wait_end;
        press(dut.u_game.dir ? 0 : 3); press(dut.u_game.dir ? 0 : 3);
        while (dut.u_game.at_end) @(negedge clk);
        $display("  two presses during one visit: level = %0d (counted once)", dut.level);
        if (dut.level != 4) errors = errors + 1;

        wait_end;
        while (dut.u_game.at_end) @(negedge clk);
        repeat (2) @(negedge clk);
        $display("  missed return: level = %0d, LED = %b", dut.level, LED);
        if (dut.level != 0) errors = errors + 1;

        for (i = 0; i < 9; i = i + 1) begin
            wait_end;
            press(dut.u_game.dir ? 0 : 3);
            while (dut.u_game.at_end && !dut.win) @(negedge clk);
        end
        $display("  after 9 returns: win = %b, level = %0d", dut.win, dut.level);
        if (!dut.win || dut.level != 9) errors = errors + 1;

        press(0);
        $display("  any button after a win restarts: win = %b, level = %0d", dut.win, dut.level);
        if (dut.win || dut.level != 0) errors = errors + 1;

        $display("RESULT tb_ping_pong_v2: %s", errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
