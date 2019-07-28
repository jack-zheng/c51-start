#include <reg52.h>
#include "digitron_drv.h"

sbit sda = P2^0;
sbit scl = P2^1;

void start(void){
	sda = 1;
	scl = 1;
	sda = 0;
}

void stop(void) {
	sda = 0;
	scl = 1;
	sda = 1;
}

void writeByte(unsigned char dat){
	unsigned char i;
	for(i=0;i<8;i++){
		scl = 0;
		if(dat & 0x80){
			sda = 1;
		}else{
		    sda = 0;
		}
		scl = 1;
		dat = dat << 1;
	}
	scl = 0;
}

unsigned char respond(void){
	unsigned char i = 0;
	unsigned char flag;
	sda = 1;
	scl = 1;
	while(1<200){
		i++;
		if(sda){
			flag = 0;
		}else{
			flag = 1;
			break;
		}
	}
	scl = 0;
	return flag;
}

void write(unsigned int dat){
	start();
	writeByte(0xa0);
	if(respond()){
	   writeByte(3);
	   if(respond()){
	   	writeByte(dat);
		if(respond()){
			stop();	// communication over, stop process.
		} else{
			stop(); // no response, stop
		}
	   }else{
	   	stop();
	   }
	}else{
		stop();
	}
}

unsigned char readByte(void){
	unsigned char i;
	unsigned char x = 0;
	for(i = 0;i < 8;i++)
	{
		scl = 1;
		x <<= 1;
		x |= (unsigned char)sda;
		scl = 0;	
	}
	return x;
}

void noRespond(void){
	sda = 1;
	scl = 1;
	scl =0;	
}

unsigned char read(void){
	unsigned char dat;
	start();
	writeByte(0xa0);
	if(respond()){
		writeByte(3);
		if(respond()){
			start();
			writeByte(0xa1);
			if(respond()){
				dat = readByte();
				noRespond();
				stop();
			}else{
				stop();
			}

		}else{
			stop();
		}
	}else{
		stop();
	}
	return dat;	
}

void delay(void){
	unsigned short i,j;
	for(i=0;i<100;i++)
		for(j=0;j<500;j++);
}

void main(void){
	unsigned char num = 0;
	unsigned short i = 0;
	num = read();
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
			write(num);
		}
		DigShowNumber(2, num/10, 0);
		DigShowNumber(1, num%10, 0);
	}
}