#include <reg52.h>

/**
1. config register
2. bps related with timer1
*/

void uartInit(void){
	SCON = 0x50; // 8bit uart
	// PCON keep as default
	// 9600 bps, config timer1, auto reset mode 2
	TH1 = 0xFD;
	TL1 = 0xFD;
	TMOD = 0x20;
	TR1 = 1; // start timer1
}

void main(void){
	unsigned char tmp;
	uartInit();
	while(1){
		if(RI){
			// already received 1 byte
			RI = 0;
			tmp = SBUF;
			if (tmp == 0x01){
				P1 = 0;
			}else{
				P1 = 0xff;
			}
		}	
	}
}