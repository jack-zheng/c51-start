#include <reg52.h>
#include "dig.h"

sbit clk = P3^6;
sbit io = P2^1;
sbit ce = P3^7;

// read second from chip

void init(){
	ce = 0;
	clk = 0;
}
/**
* CE to high
*/
unsigned int readData(){
	unsigned char sec_addr = 0x8d;
	unsigned char i;
	unsigned int ret;
	init();

	ce = 1;
	// give command to ds chip
	for(i=0;i<8;i++){
		clk = 0;
		if(sec_addr&0x01){
			io = 1;
		}else{
			io = 0;
		}
		clk = 1;
		sec_addr >>= 1;
	}
	
	// read sec value
	for(i=0;i<8;i++){
		clk = 0;
		ret >>= 1;

		if(io){
			ret |= 0x80;
		}else{
			ret &= ~0x80;
		}
		clk = 1;
	}
	
	return (ret);	    
}
//	unsigned char year_addr = 0x8c;
	//unsigned int year_val = 0x19;
void writeData(unsigned char addr, unsigned char val){

	unsigned char i;

	init();

	ce = 1;
	// give command to ds chip
	for(i=0;i<8;i++){
		clk = 0;
		if(addr&0x01){
			io = 1;
		}else{
			io = 0;
		}
		clk = 1;
		addr >>= 1;
	}
	
	// write year value
	for(i=0;i<8;i++){
		clk = 0;
		if(val & 0x01)
		{
			io = 1;
		}else{
			io = 0;
		}
		clk = 1;
		val >>= 1;
	}
}

void main(void){
	unsigned int ret;
	// turn off WP
	writeData(0x8e, 0x00);
	// write year
	writeData(0x8c, 0x19);
	// turn of WP
	writeData(0x8e, 0x80);
	while(1){
		ret = readData();
		
		display(ret);
	}
}