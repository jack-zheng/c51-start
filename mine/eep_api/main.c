#include <reg52.h>
#include "digitron_drv.h"
#include "IIC_drv.h"

void main(void){
	unsigned char num = 0;
	unsigned short i = 0;
	//ReadIIC(unsigned char device,unsigned char address);
	num = ReadIIC(0xa0, 10);
	if(num>99){
			num = 0;
	}
	while(1){
		i++;
		if (i>500){
			i=0;
			num++;
			if(num>12){
				num=0;
			}
			//WriteIIC(unsigned char device,unsigned char address,unsigned char temp);
			WriteIIC(0xa0, 10, num);
		}
		DigShowNumber(2, num/10, 0);
		DigShowNumber(1, num%10, 0);
	}
}