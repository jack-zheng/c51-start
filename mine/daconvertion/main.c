#include <reg52.h>
#include "IIC_drv.h"

/**
* cause for MCU, it is unable to out put voltage like 1.3 or 2.8, os we need 
* AD/DA chip to help us to finish such kind of function.
*/
void main(void){
	// void WriteIIC(unsigned char device,unsigned char address,unsigned char temp);
	unsigned char state;
	unsigned char input = 0x00;
	unsigned short i = 0;

	while(1){
		i++;
		if (i>700){
			i=0;
			if(input == 0){
				state = 0;
			}

			if (input == 255){
				state = 1;
			}

			if(state == 0){
				WriteIIC(0x90, 0x40, input++);
			}
			else{
				WriteIIC(0x90, 0x40, input--);
			}
		}
	}
}