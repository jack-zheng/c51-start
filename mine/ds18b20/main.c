#include <reg52.h>
#include "digitron.h"
#include "intrins.h"

sbit DQ = P1^4;

/*0.5c = 0x08*/

// init
// search device - 0xcc skip search device
// 0x44 wait for temporary transfer
// 0xBE read 

void writeByte(unsigned char dat){
	unsigned char i;
	for(i=0;i<8;i++){
		if((dat & 0x01) == 0x01){
		   
			// get 1
			DQ = 0;
			Delay(1);
			DQ = 1;
			Delay(25);
		}else{
			// get 0
			DQ = 0; // 60us - 120us
			Delay(25); // 25*3us near to 75us
			DQ = 1;
			Delay(1);
		}
		dat >>= 1;
	}
}

unsigned char readByte(void){
	unsigned char dat, i;
	dat = 0;
	for(i=0;i<8;i++){
		// read 0
		dat >>= 1;
		DQ = 0;
		Delay(1);
		DQ = 1;
		_nop_();
		if (DQ)
		{
			dat |= 0x80;
		}else
		{
		}
		Delay(25)
	}
}

unsigned char init(void){
	unsigned char exist;
	// if device exist, return 1, or return 0
	DQ = 0;
	Delay(200);
	DQ = 1;
	Delay(25);
	if(!DQ){
		exist = 1;
	}else{
		exist = 0;
	}
	Delay(200);
	return exist;
}

void main(void){
	unsigned short int dat;
	unsigned  char low8;
	unsigned  char high8;

	while(1){
		switch(DS_Step){
			case 0:	  // transfer
				if (init()){
					writeByte(0xcc);	
					writeByte(0x44);
					Cnt = 0;
					DS_Step = 1;
				}
				break;
			case 1:	  // wait
				if (Cnt++ > 2000){
					cnt = 0;
					DS_Step = 2;
				}
				break;
			case 2:
				if (init()){
					writeByte(0xcc);	
					writeByte(0xbe);

					low8 = 	readByte();
					high8 = readByte();

					dat = high8;
					dat = (dat<<8) + low8;

					// transfer temporary
					dat = dat * 5/8;

					

					DS_Step = 0;
				}
				break;
			default:
				break;
		}
	}
}