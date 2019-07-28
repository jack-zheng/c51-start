#include <reg52.h>
#include "digitron_drv.h"
#include "IIC_drv.h"

unsigned short convertAnalogToDigital(unsigned int analog){
	unsigned long int tmp;
	tmp = analog * 500L;	//append 'L' to enforce data type to long
	tmp  = tmp/255;
	return tmp; 			  	
}

void main(void){
	unsigned int dat = 0;
	unsigned short i = 0;

	while(1){
		i++;
		if (i>500){
			i=0;
			dat = ReadIIC(0x90, 0x02);
			dat = convertAnalogToDigital(dat);
		}
		DigShowNumber(3, dat/100, TRUE);
		DigShowNumber(2, dat%100/10, 0);
		DigShowNumber(1, dat%10, 0);
	}
}