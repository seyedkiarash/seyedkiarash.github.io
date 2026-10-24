// Reference model shared by the testbenches: hex digit -> active-low segments,
// and the inverse (segments -> printable character, '?' if not a digit).
function [6:0] seg_of;
    input [3:0] h;
    case (h)
        4'h0: seg_of = ~7'b1111110; 4'h1: seg_of = ~7'b0110000;
        4'h2: seg_of = ~7'b1101101; 4'h3: seg_of = ~7'b1111001;
        4'h4: seg_of = ~7'b0110011; 4'h5: seg_of = ~7'b1011011;
        4'h6: seg_of = ~7'b1011111; 4'h7: seg_of = ~7'b1110000;
        4'h8: seg_of = ~7'b1111111; 4'h9: seg_of = ~7'b1111011;
        4'hA: seg_of = ~7'b1110111; 4'hB: seg_of = ~7'b0011111;
        4'hC: seg_of = ~7'b1001110; 4'hD: seg_of = ~7'b0111101;
        4'hE: seg_of = ~7'b1001111; 4'hF: seg_of = ~7'b1000111;
    endcase
endfunction

function [7:0] char_of;
    input [6:0] s;
    integer h;
    begin
        char_of = "?";
        if (s == 7'b1111111) char_of = " ";
        for (h = 0; h < 16; h = h + 1)
            if (seg_of(h) == s) char_of = (h < 10) ? ("0" + h) : ("A" + h - 10);
    end
endfunction
