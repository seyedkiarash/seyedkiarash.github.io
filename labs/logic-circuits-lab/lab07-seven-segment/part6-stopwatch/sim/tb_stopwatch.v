`timescale 1ns/1ps

module tb_stopwatch;
    `include "seg_model.vh"
    reg clk = 0; always #10 clk = ~clk;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    stopwatch #(.TICK_HALF_PERIOD(16), .SCAN_HALF_PERIOD(1))
        dut (.clk(clk), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .dig(dig));

    integer ticks = 0, errors = 0, checks = 0, k, t;
    reg [31:0] frame, want; reg [7:0] c3, c2, c1, c0;
    always @(posedge dut.tick_clk) ticks = ticks + 1;

    initial begin
        $dumpfile("tb_stopwatch.vcd"); $dumpvars(1, tb_stopwatch); $dumpvars(1, dut);
        #200_000 $dumpoff;
    end

    initial begin
        repeat (6003) begin
            @(posedge dut.tick_clk); repeat (12) @(negedge clk);
            frame = "????";
            repeat (8) begin
                @(negedge clk);
                for (k = 0; k < 4; k = k + 1)
                    if (dig == (4'b1000 >> k)) frame[8*(3-k) +: 8] = char_of({a,b,c,d,e,f,g});
            end
            t = ticks % 6000;
            c3 = "0" + t/600; c2 = "0" + (t/100)%6; c1 = "0" + (t/10)%10; c0 = "0" + t%10;
            want = {c3, c2, c1, c0};
            checks = checks + 1;
            if (frame !== want) begin
                errors = errors + 1;
                if (errors < 5) $display("  mismatch after %0d ticks: shows %s, expected %s", ticks, frame, want);
            end
            if (ticks == 5999 || ticks == 6000) $display("  after %0d ticks the display reads %s", ticks, frame);
        end
        $display("RESULT tb_stopwatch: %0d ticks checked (full 9:59.9 -> 0:00.0 roll-over), %0d errors -> %s",
                 checks, errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
