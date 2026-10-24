`timescale 1ns/1ps
module tb_display_1234;
    `include "seg_model.vh"
    reg clk = 0; always #10 clk = ~clk;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    display_1234 #(.SCAN_HALF_PERIOD(2)) dut (.clk(clk), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .dig(dig));
    reg [31:0] frame = "????";
    integer k, errors = 0;
    initial begin
        $dumpfile("tb_display_1234.vcd"); $dumpvars(0, tb_display_1234);
        repeat (4) @(negedge clk);
        repeat (400) begin
            @(negedge clk);
            for (k = 0; k < 4; k = k + 1)
                if (dig == (4'b1000 >> k)) frame[8*(3-k) +: 8] = char_of({a,b,c,d,e,f,g});
            if ($countones(dig) != 1) errors = errors + 1;   // exactly one digit on
        end
        $display("RESULT tb_display_1234: persistent frame = \"%s\", one-hot violations = %0d", frame, errors);
        $display("RESULT tb_display_1234: %s", (frame == "1234" && errors == 0) ? "PASS" : "FAIL");
        $finish;
    end
endmodule
