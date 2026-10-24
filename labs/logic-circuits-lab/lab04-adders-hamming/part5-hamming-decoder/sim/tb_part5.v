`timescale 1ns/1ps
module tb_part5;
    reg [7:0] Dip = 0; wire [9:0] LED; wire [3:0] dig; wire a,b,c,d,e,f,g;
    Part5_module dut (.Dip(Dip), .LED(LED), .dig(dig), .a(a),.b(b),.c(c),.d(d),.e(e),.f(f),.g(g));
    // independent reference encoder: positions 1..7 = p0 p1 x0 p2 x1 x2 x3
    reg [3:0] data; wire [6:0] code;
    assign code = {data[3]^data[2]^data[0], data[3]^data[1]^data[0], data[3],
                   data[2]^data[1]^data[0], data[2], data[1], data[0]};
    integer i, pos, errors = 0;
    initial begin
        $dumpfile("tb_part5.vcd"); $dumpvars(0, tb_part5);
        for (i = 0; i < 16; i = i + 1)
            for (pos = 0; pos <= 7; pos = pos + 1) begin      // pos 0 = no error
                data = i; #1;
                Dip = {(pos == 0) ? code : code ^ (7'b1000000 >> (pos - 1)), 1'b0}; #10;
                if (LED[3:0] !== data) errors = errors + 1;
                if (dut.err !== pos) errors = errors + 1;
            end
        $display("RESULT tb_part5: 16 words x (no error + 7 single errors) = 128 cases, %0d errors -> %s", errors, errors ? "FAIL" : "PASS");
        $finish;
    end
endmodule
