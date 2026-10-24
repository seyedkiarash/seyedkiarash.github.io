// -----------------------------------------------------------------------------
// Lab 7 - Bonus C: "Snake" running around the 4-digit display
//
// The outer segments of the four digits form a ring of 12 positions:
//
//      0     1     2     3            positions 0-3  : segment a, left -> right
//    -----  ----  ----  -----        positions 4-5  : segments b, c of digit 0
//  11|                    |4         positions 6-9  : segment d, right -> left
//  10|                    |5         positions 10-11: segments e, f of digit 3
//    -----  ----  ----  -----
//      9     8     7     6
//
// A 3-segment snake (head, head-1, head-2) moves one position per move tick.
// Free-running counters provide the timing (taps of a binary counter):
//   scan_clk = bit 16 -> 50 MHz / 2^17 ~ 381 Hz digit scan
//   move_clk = bit 24 -> 50 MHz / 2^25 ~ 1.5 Hz snake step
//
// DIGIT_ACTIVE_LOW: the submitted version drove the digit enables active-low
// (e.g. 1110 selects digit 0), while every other part of this lab drives them
// active-high (0001). The parameter keeps the submitted behaviour by default;
// set it to 0 to match the polarity used in Parts 3-6.
// -----------------------------------------------------------------------------
module snake_display #(
    parameter integer SCAN_BIT         = 16,
    parameter integer MOVE_BIT         = 24,
    parameter         DIGIT_ACTIVE_LOW = 1
) (
    input  wire       clk,                      // 50 MHz
    output reg        a, b, c, d, e, f, g,      // active-low segments
    output reg  [3:0] dig
);

    // ---- timing --------------------------------------------------------------
    reg [MOVE_BIT:0] div = 0;
    always @(posedge clk) div <= div + 1'b1;

    wire scan_clk = div[SCAN_BIT];
    wire move_clk = div[MOVE_BIT];

    // ---- snake position --------------------------------------------------------
    reg [3:0] head_pos = 4'd0;                  // 0..11
    always @(posedge move_clk)
        head_pos <= (head_pos == 4'd11) ? 4'd0 : head_pos + 4'd1;

    // ---- frame: which segments are lit on each digit ---------------------------
    // Pattern bits: 6=a 5=b 4=c 3=d 2=e 1=f 0=g (positive logic)
    reg [6:0] digit_patterns [3:0];
    reg [1:0] target_digit;
    reg [6:0] target_mask;
    integer   i, k, pos;

    always @(*) begin
        for (i = 0; i < 4; i = i + 1) digit_patterns[i] = 7'b0;

        for (k = 0; k < 3; k = k + 1) begin
            pos = (head_pos >= k) ? head_pos - k : 12 - (k - head_pos);
            case (pos)
                0:  begin target_digit = 2'd3; target_mask = 7'b1000000; end // a
                1:  begin target_digit = 2'd2; target_mask = 7'b1000000; end
                2:  begin target_digit = 2'd1; target_mask = 7'b1000000; end
                3:  begin target_digit = 2'd0; target_mask = 7'b1000000; end
                4:  begin target_digit = 2'd0; target_mask = 7'b0100000; end // b
                5:  begin target_digit = 2'd0; target_mask = 7'b0010000; end // c
                6:  begin target_digit = 2'd0; target_mask = 7'b0001000; end // d
                7:  begin target_digit = 2'd1; target_mask = 7'b0001000; end
                8:  begin target_digit = 2'd2; target_mask = 7'b0001000; end
                9:  begin target_digit = 2'd3; target_mask = 7'b0001000; end
                10: begin target_digit = 2'd3; target_mask = 7'b0000100; end // e
                11: begin target_digit = 2'd3; target_mask = 7'b0000010; end // f
                default: begin target_digit = 2'd0; target_mask = 7'b0; end
            endcase
            digit_patterns[target_digit] = digit_patterns[target_digit] | target_mask;
        end
    end

    // ---- multiplexing ----------------------------------------------------------
    reg [1:0] scan_idx = 2'd0;
    always @(posedge scan_clk) scan_idx <= scan_idx + 2'd1;

    wire [3:0] one_hot = 4'b0001 << scan_idx;   // digit 0 = rightmost

    always @(*) begin
        dig             = DIGIT_ACTIVE_LOW ? ~one_hot : one_hot;
        {a,b,c,d,e,f,g} = ~digit_patterns[scan_idx];
    end

endmodule
