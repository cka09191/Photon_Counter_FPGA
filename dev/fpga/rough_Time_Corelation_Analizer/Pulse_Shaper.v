module Pulse_Shaper(
	input wire clk,// 500MHz
	input wire channel,
	output reg pulse
);

reg [7:0] count; // 8 bit counter for dead time:60ns, pulse width:2ns
reg activate;

initial begin
    activate = 0;
    count = 8'd127;
	pulse <= 0;
end



always @(posedge clk) begin
	if(activate) begin
		case(count)
			8'd20: begin
				activate = 0;
				count = 8'h00;
			end
			default: begin
				pulse <= 0;
				count <= count + 1;
			end
		endcase
	end
	else begin
		if(channel) begin 
			activate=1;
			pulse <= 1;
		end
	end
end

endmodule
