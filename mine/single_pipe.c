#include "reg52.h"

// In this script snippet, I will light the first digital pipe.
// the order should be 0000, 0110, 0000, 0001 input order is from left to right

sbit dig_data = P0^2;
sbit shcp = P0^4;
sbit stcp = P2^3;

// 共阳二极管，显示位取反
code unsigned char serials[] = {1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,1}; 

void main(void){
	unsigned int i;
	// init port
	shcp = 0;
	stcp = 0;													

	// loop data into shift register
	for(i=0;i<16;i++){
		dig_data = serials[i];
		shcp = 1;
		shcp = 0;
	}

	// data transfer from shift register to storage register
	stcp = 1;

	// hold output
	while(1){}
}
