#include <reg52.h>

/*
how to write a driver
1. init config
2. module read
3. module write
*/

sbit RS = P2^7;
sbit RW = P2^6;
sbit E = P2^5;

unsigned char busyCheck(void){
	P0 = 0xff;
	RS = 0;
	RW = 1;
	E = 0;
	E = 1;
	return (P0&0x80);
}

// RS = 0, write to command register
void writeInstructionCode(unsigned char cmd){
	while(busyCheck());
	RS = 0;	// write command
	RW = 0; // do write
	E = 1;
	P0 = cmd;
	E = 0;
}

// RS = 1, write to data register
void writeDataCode(unsigned char dat){
	while(busyCheck());
 	RS = 1;	// write data
	RW = 0; // do write
	E = 1;
	P0 = dat;
	E = 0;
}

void init(void){
	 writeInstructionCode(0x38); // data transfer 8 bit, 2 lines show out
	 writeInstructionCode(0x08); // turn off display
	 writeInstructionCode(0x01); // clear display
	 writeInstructionCode(0x06); // assign cursor moving direction, enable shift display
	 writeInstructionCode(0x0f); // turn on screen, cursor and blink
}


void main(void){
	unsigned char *str = "Hello World";
	init();

	writeInstructionCode(0x83); // set the start position, start from line 1, position 3.
	while(*str != '\0'){
		writeDataCode(*str);
		str++;
	}
	while(1);

}