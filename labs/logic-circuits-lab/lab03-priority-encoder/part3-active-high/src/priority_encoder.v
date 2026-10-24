// -----------------------------------------------------------------------------
// Lab 3 - Part 3: 4-input priority encoder (buttons treated as active-high)
// The highest-numbered pressed button wins; its number + 1 is shown in binary
// on LED[2:0] (000 = no button pressed).
//   button[3] -> 100   button[2] -> 011   button[1] -> 010   button[0] -> 001
// -----------------------------------------------------------------------------
module priority_encoder (
    input  wire [3:0] button,
    output reg  [4:0] LED
);
    always @(*) begin
        if      (button[3]) LED = 5'b00100;
        else if (button[2]) LED = 5'b00011;
        else if (button[1]) LED = 5'b00010;
        else if (button[0]) LED = 5'b00001;
        else                LED = 5'b00000;
    end
endmodule
