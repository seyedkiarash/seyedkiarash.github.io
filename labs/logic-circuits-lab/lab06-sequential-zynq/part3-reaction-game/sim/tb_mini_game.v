`timescale 1ns/1ps
// Unit test of the game FSM, clocked directly by the testbench (one clock
// = one step of the light). The player presses at the right time four times
// (levels 0-3) and wins; then a mistimed press is checked.
module tb_mini_game;
    reg clk = 0, gameReset = 1;
    reg [3:0] button = 0;
    wire [4:0] LED; wire [1:0] mode;
    mini_game dut (.clk(clk), .gameReset(gameReset), .button(button), .LED(LED), .mode(mode));

    task tick; begin #50 clk = 1; #50 clk = 0; end endtask
    task press_when(input [4:0] pattern);
        begin
            while (LED !== pattern) tick;
            button[2] = 1; tick; button[2] = 0;
        end
    endtask
    integer lvl, errors = 0;
    initial begin
        $dumpfile("tb_mini_game.vcd"); $dumpvars(0, tb_mini_game);
        #20 gameReset = 0;
        for (lvl = 0; lvl < 4; lvl = lvl + 1) begin
            if (mode !== lvl) errors = errors + 1;
            press_when(5'b00100);                       // hit on the middle LED
        end
        tick;
        $display("  after 4 hits: LED=%b (win = 11111)", LED);
        if (LED !== 5'b11111) errors = errors + 1;
        button[2] = 1; tick; button[2] = 0;             // new game
        press_when(5'b00100);                           // level 1
        press_when(5'b01000);                           // miss -> level 0
        $display("  after a hit and a miss: level=%0d", mode);
        if (mode !== 0) errors = errors + 1;
        $display("RESULT tb_mini_game: %s", errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
