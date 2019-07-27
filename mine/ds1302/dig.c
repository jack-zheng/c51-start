#include "intrins.h"
#include "dig.h"

// the common port of pipes is Vcc
unsigned char pos[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x98, 0xc0};

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

// give val and show on pipe
void display(unsigned char val){
	showNumber(num[val>>4], pos[1]);
	showNumber(num[val&0x0f], pos[0]);
}