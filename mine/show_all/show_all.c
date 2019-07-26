/**
* In this sample, I will loop and show 1-8 in all pipes the same time
*/
#include "reg52.h"
#include "intrins.h"

sbit dig_data = P0^2;
sbit shcp = P0^4;
sbit stcp = P2^3;

// the common port of pipes is Vcc
code unsigned char position[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
code unsigned char num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x98, 0xc0};

void showNumber(unsigned char num, unsigned char pos){
	unsigned short i;
	shcp=0;
	stcp=0;
	for(i=0;i<8;i++){
		dig_data = num&0x80;
		_nop_();
		shcp = 1;
		_nop_();
		shcp = 0;
		num <<= 1;
	}

	for(i=0;i<8;i++){
		dig_data = pos&0x80;
		_nop_();
		shcp = 1;
		_nop_();
		shcp = 0;
		pos <<= 1;
	}
	stcp = 1;
	_nop_();
}

void main(void){
	unsigned char i;
	
	for(i=0;i<8;i++){
		showNumber(num[i], position[i]);
	}

}