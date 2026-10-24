// -----------------------------------------------------------------------------
// Two's complement -> sign / magnitude (for display)
// -----------------------------------------------------------------------------
module twos_to_sign_mag (
    input  wire [3:0] TwosComp,
    output wire       Sign,
    output wire [3:0] Mag
);
    assign Sign = TwosComp[3];
    assign Mag  = Sign ? (~TwosComp + 4'd1) : TwosComp;
endmodule
