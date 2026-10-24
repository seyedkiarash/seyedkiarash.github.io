`timescale 1ns/1ps
module tb_show_student_id;
    `include "seg_model.vh"
    reg clk = 0; always #10 clk = ~clk;
    wire a,b,c,d,e,f,g; wire [3:0] dig;
    show_student_id #(.STEP_HALF_PERIOD(4)) dut (.clk(clk), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g), .dig(dig));
    reg [8*10-1:0] seen = "";

    reg [7:0] ch, last = "x";
    integer n = 1;
    initial begin
        $dumpfile("tb_show_student_id.vcd"); $dumpvars(0, tb_show_student_id);
        repeat (4) @(negedge clk);
        repeat (2000) begin
            @(negedge clk);
            ch = char_of({a,b,c,d,e,f,g});
            if (dig == 4'b1111 && n < 10 && dut.state == n) begin
                seen = {seen[8*9-1:0], ch}; n = n + 1;
            end
        end

        wait (dut.state == 4'd0); repeat (2) @(negedge clk);
        seen = {char_of({a,b,c,d,e,f,g}), seen[8*9-1:0]};
        $display("RESULT tb_show_student_id: sequence shown = %s (expected 4031013830)", seen);
        $display("RESULT tb_show_student_id: %s", (seen == "4031013830") ? "PASS" : "FAIL");
        $finish;
    end
endmodule
