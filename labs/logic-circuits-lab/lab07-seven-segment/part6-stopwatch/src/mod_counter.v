// -----------------------------------------------------------------------------
// mod_counter
// Synchronous modulo-(N+1) counter with enable and carry-out ("done").
// It counts 0..N while enable is high; done is asserted combinationally when
// the counter is at N and enabled, i.e. exactly when the NEXT counter in a
// cascade must advance. Chaining done -> enable builds a multi-digit counter.
// -----------------------------------------------------------------------------
module mod_counter (
    input  wire [3:0] N,          // terminal count (9 for a decade, 5 for 0..5)
    input  wire       clk,
    input  wire       enable,
    output reg  [3:0] number = 4'd0,
    output wire       done
);

    always @(posedge clk)
        if (enable)
            number <= (number == N) ? 4'd0 : number + 4'd1;

    assign done = enable && (number == N);

endmodule
