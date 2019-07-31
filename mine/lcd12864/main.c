#include <reg52.h>
#include <intrins.h>

#define DATA P0

sbit LCD_RS = P2^7;
sbit LCD_RW = P2^6;
sbit LCD_EN = P2^5;
sbit LCD12864_PSB = P2^4;


void Delay(unsigned short int dly){
	while(dly--);
}

bit readBusyFlag(void){
	unsigned char dat;
	LCD_EN = 0;
	LCD_RS = 0;
	LCD_RW = 1;


	LCD_EN = 1;
	dat = DATA;
	LCD_EN = 0;
	return dat&0x80;
}

void writeCommand(unsigned char cmd){
	//while(readBusyFlag());
	Delay(100);
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 1;
	DATA = cmd;
	_nop_();
	LCD_EN = 0;
}

void writeData(unsigned char dat){
	//while(readBusyFlag());
	Delay(100);
	Delay(100);
 	LCD_RS = 1;
	LCD_RW = 0;
	LCD_EN = 1;
	DATA = dat;
	_nop_();
	LCD_EN = 0;
}


void init(void){
 

	LCD12864_PSB = 1;
	writeCommand(0x30);
	writeCommand(0x0c);
	writeCommand(0x01);
	writeCommand(0x06);
}

void main(void){
	unsigned char *str = "aÄã";
	init();
	while(*str != '\0'){
		writeData(*str);
		str++;
	}
	while(1);
}