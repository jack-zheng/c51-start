/**
* In this sample, I will loop and show 1-9 on the first digital pipe
*/
#include "reg52.h"
#include "intrins.h"

sbit dig_data = P0^2;
sbit shcp = P0^4;
sbit stcp = P2^3;

// the common port of pipes is Vcc
code unsigned char position = 0x01;
code unsigned char num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x98, 0xc0};

void delay() {
	unsigned int i,j;
	for (i=0;i<1000;i++)
		for(j=0;j<100;j++);
}

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
	delay();
}

void main(void){
	unsigned char i;
	while(1){
		for (i=0;i<10;i++){
			showNumber(num[i], position);
		}
	}
}