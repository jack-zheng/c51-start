#include <reg52.h>
#include <intrins.h>

sbit dig_data = P0^2;
sbit shcp = P0^4;
sbit stcp = P2^3;

// show segment number
code unsigned char segment[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 
// select segment
code unsigned char select[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void delay(){
	unsigned int i,j;
	for(i=0;i<100;i++){
		for(j=0;j<100;j++){}
	}
}

void digOutput(unsigned char selectByte, unsigned char segmentByte){
	unsigned char i;
	shcp = 0;
	stcp = 0;
	for (i=0;i<8;i++){
		if(segmentByte&0x80){
			dig_data = 1;
		}else{
			dig_data = 0;
		}
		_nop_();
		shcp = 1;
		_nop_();
		shcp = 0;
		_nop_();
		segmentByte <<= 1;
	}

	// store position to chip
	for(i=0;i<8;i++){
		if(selectByte&0x80){
			dig_data = 1;
		}else{
			dig_data = 0;
		}
		_nop_();
		shcp = 1;
		_nop_();
		shcp = 0;
		_nop_();
		selectByte <<= 1;
	}

	// output status to pin and lock;
	stcp = 1;
	_nop_();
	stcp = 0;
	_nop_();
	delay();
}

void main(void){
	while(1){
	   digOutput(select[8], segment[1]);
	   digOutput(select[7], segment[2]);
	   digOutput(select[6], segment[3]);
	   digOutput(select[5], segment[4]);
	   digOutput(select[4], segment[5]);
	   digOutput(select[3], segment[6]);
	   digOutput(select[2], segment[7]);
	   digOutput(select[1], segment[8]);
	}
}