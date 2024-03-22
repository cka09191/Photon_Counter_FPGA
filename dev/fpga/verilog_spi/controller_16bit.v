
/*
basic FPGA Controller module in 16bit
    CLK:
        clock signal to synchronize
        at rising edge of CLK, COMMAND signal is valid

    COMMAND:
        signal from master, from SPI module
        0x00: idle(stop counting),
		0x01: start counting
    START_COUNT:
        signal to indicate start of counting

* @author Gyeongjun Chae(https://github.com/cka09191)
 */

module controller(
    input wire CLK,
    input wire DMD,
    output reg START_COUNT
    );  // BYTE received is valid

	reg [2:0] DMD_r;  always @(posedge CLK) DMD_r <= { DMD_r[1:0], DMD };
	wire DMD_rising  = ( DMD_r[2:1] == 2'b01 );
	wire DMD_falling = ( DMD_r[2:1] == 2'b10 );
	 
    always @(posedge CLK) begin
        if (DMD_rising) begin
            START_COUNT <= 1;
        end
        if (DMD_falling) begin
            START_COUNT <= 0;
        end
    end
	 
endmodule