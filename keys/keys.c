#include <reg52.h>
#include "digitron_drv.h"
#define unit unsigned int
#define uchar unsigned char
uchar key_num;

void delay(uchar x){
	uchar i,j;
	for(i=x;i>0;i--)
		for(j=100;j>0;j--);
}

void display(void){
	DigShowNumber(1, key_num%10, 0);
	DigShowNumber(2, key_num/10, 0);
}

void keyBoard(void){
	uchar tmp;

	P1 = 0xef;
	tmp = P1;
	tmp = tmp&0x0f;
	if (tmp!=0x0f){
		delay(10);
		tmp = P1;
		tmp = tmp&0x0f;
		if (tmp!=0x0f){
			tmp = P1;
			switch(tmp){
				case 0xee: // if p1 = 0xee, 7 is pushed
					key_num = 7;
					break;
				case 0xed:
					key_num = 4;
					break;
				case 0xeb:
					key_num = 1;
					break;
				case 0xe7:
					key_num = 0;
					break;
			}
		}
		while(tmp!=0x0f){
			tmp = P1;
			tmp = tmp&0x0f;
			
			display();
		}
	} 

	P1 = 0xdf;
	tmp = P1;
	tmp = tmp&0x0f;
	if (tmp!=0x0f){
		delay(10);
		tmp = P1;
		tmp = tmp&0x0f;
		if (tmp!=0x0f){
			tmp = P1;
			switch(tmp){
				case 0xde: // if p1 = 0xee, 7 is pushed
					key_num = 8;
					break;
				case 0xdd:
					key_num = 5;
					break;
				case 0xdb:
					key_num = 2;
					break;
				case 0xd7:
					key_num = 10;
					break;
			}
		}
		while(tmp!=0x0f){
			tmp = P1;
			tmp = tmp&0x0f;
			
			display();
		}
	}

	P1 = 0xbf;
	tmp = P1;
	tmp = tmp&0x0f;
	if (tmp!=0x0f){
		delay(10);
		tmp = P1;
		tmp = tmp&0x0f;
		if (tmp!=0x0f){
			tmp = P1;
			switch(tmp){
				case 0xbe: // if p1 = 0xee, 7 is pushed
					key_num = 9;
					break;
				case 0xbd:
					key_num = 6;
					break;
				case 0xbb:
					key_num = 3;
					break;
				case 0xb7:
					key_num = 11;
					break;
			}
		}
		while(tmp!=0x0f){
			tmp = P1;
			tmp = tmp&0x0f;
			
			display();
		}
	}

	P1 = 0x7f;
	tmp = P1;
	tmp = tmp&0x0f;
	if (tmp!=0x0f){
		delay(10);
		tmp = P1;
		tmp = tmp&0x0f;
		if (tmp!=0x0f){
			tmp = P1;
			switch(tmp){
				case 0x7e: // if p1 = 0xee, 7 is pushed
					key_num = 12;
					break;
				case 0x7d:
					key_num = 13;
					break;
				case 0x7b:
					key_num = 14;
					break;
				case 0x77:
					key_num = 115;
					break;
			}
		}
		while(tmp!=0x0f){
			tmp = P1;
			tmp = tmp&0x0f;
			
			display();
		}
	}
}

void main(void){
	while(1){
		keyBoard();
		display();
	}
}