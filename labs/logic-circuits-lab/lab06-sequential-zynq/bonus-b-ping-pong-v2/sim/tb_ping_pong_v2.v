`timescale 1ns/1ps
module tb_ping_pong_v2;
    reg clk = 0; always #10 clk = ~clk;
    reg reset = 1, tick = 0;
    reg [3:0] button = 0;
    wire [4:0] leds; wire [3:0] level; wire over;
    game_logic dut (.clk(clk), .reset(reset), .move_tick(tick), .button(button),
                    .leds(leds), .level(level), .game_over_flag(over));
    // the real pulse generator, checked separately for its tick period
    reg pg_reset = 1; reg [3:0] pg_level = 4'd8;   // set to 9 after start: a change
    // is needed so that the always @(*) block evaluates in simulation wire pg_tick;
    pulse_generator pg (.clk(clk), .reset(pg_reset), .level(pg_level), .tick(pg_tick));

    task move; begin @(negedge clk) tick = 1; @(negedge clk) tick = 0; repeat (2) @(negedge clk); end endtask
    task press(input integer k); begin @(negedge clk) button[k] = 1; repeat (2) @(negedge clk); button[k] = 0; @(negedge clk); end endtask
    integer errors = 0, hits = 0; time t0, t1;
    initial begin
        $dumpfile("tb_ping_pong_v2.vcd"); $dumpvars(0, tb_ping_pong_v2);
        repeat (2) @(negedge clk); reset = 0; pg_reset = 0; pg_level = 4'd9;
        while (!over && hits < 20) begin
            move;
            if (dut.pos == 3'd4) begin press(3); hits = hits + 1; end
            if (dut.pos == 3'd0) begin press(0); hits = hits + 1; end
        end
        repeat (2) @(negedge clk);
        $display("  %0d returns -> level %0d, game_over=%b, LEDs=%b", hits, level, over, leds);
        if (!(over && leds == 5'b11111 && hits == 9)) errors = errors + 1;
        @(posedge pg_tick) t0 = $time; @(posedge pg_tick) t1 = $time;
        $display("  pulse_generator, level 9: one tick every %0d cycles", (t1 - t0) / 20);
        if ((t1 - t0) / 20 != 20001) errors = errors + 1;
        $display("RESULT tb_ping_pong_v2: %s", errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
