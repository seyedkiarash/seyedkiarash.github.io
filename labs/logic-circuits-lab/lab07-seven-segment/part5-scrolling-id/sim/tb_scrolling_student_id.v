`timescale 1ns/1ps
module tb_scrolling_student_id;
    `include "seg_model.vh"
    reg clk = 0; always #10 clk = ~clk;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    scrolling_student_id #(.SHIFT_HALF_PERIOD(64), .SCAN_HALF_PERIOD(2))
        dut (.clk(clk), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g));
    reg [31:0] frame; integer k, w, errors = 0;
    reg [8*36-1:0] expected = "403103103101101301381383383483403403";
    initial begin
        $dumpfile("tb_scrolling_student_id.vcd"); $dumpvars(0, tb_scrolling_student_id);
        @(posedge dut.shift_clk);
        for (w = 0; w < 9; w = w + 1) begin
            repeat (64) @(negedge clk);
            frame = "????";
            repeat (20) begin
                @(negedge clk);
                for (k = 0; k < 4; k = k + 1)
                    if (dig == (4'b1000 >> k)) frame[8*(3-k) +: 8] = char_of({a,b,c,d,e,f,g});
            end
            $display("  window %0d: display reads \"%s\"", dut.state_show, frame);
            if (frame != expected[8*4*(8-dut.state_show) +: 32]) errors = errors + 1;
            @(posedge dut.shift_clk);
        end
        $display("RESULT tb_scrolling_student_id: 9 windows checked, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
