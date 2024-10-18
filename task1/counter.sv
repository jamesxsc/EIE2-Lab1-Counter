module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input   logic               clk,    // clock
    input   logic               rst,    // reset
    input   logic               en,     // counter enable
    output  logic [WIDTH-1:0]   count   // count output
);

always_ff @ (posedge clk)
    if (rst)    count <= {WIDTH{1'b0}}; // non-blocking assignment, since we are in always_ff block
    else        count <= count + {{WIDTH-1{1'b0}}, en}; // construct concats 7 bits of 0 and either 1 or 0 depending on if en is high which is added to count
    
endmodule
