module counterchallenge #(
    parameter WIDTH = 8  // Counter width
)(
    input logic clk,
    input logic rst,
    input logic en,  // en now controls the counting direction
    output logic [WIDTH-1:0] count
);

    always_ff @(posedge clk) begin
        if (rst) begin
            count <= {WIDTH{1'b0}};  // reset the counter to 0
        end else begin
            if (en) begin
                count <= count + 1;  // count up when en is 1
            end else begin
                count <= count - 1;  // count down when en is 0
            end
        end
    end

endmodule
