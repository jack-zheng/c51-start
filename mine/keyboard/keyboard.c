#include "reg52.h"
#include "dig.h"
#define uchar unsigned char

uchar key_num;

// show 12 on the firt and second position


void display(uchar val){
	showNumber(num[val/10], pos[1]);
	showNumber(num[val%10], pos[0]);
}

void delay(uchar x)
{
	uchar i,j;
	for(i = x;i > 0;i--)
		for(j = 100;j > 0;j--);
}

void getKeyNum(){
	 uchar out;
	 // first row check
	 P1 = 0xfe;
	 out = P1;
	 switch(out){
	 	case 0xee:
			key_num = 7;
			break;
		case 0xde:
			key_num = 8;
			break;
		case 0xbe:
			key_num = 9;
			break;
		case 0x7e:
			key_num = 15;
			break;
	 }

 	 // second row check
	 P1 = 0xfd;
	 out = P1;
	 switch(out){
	 	case 0xed:
			key_num = 4;
			break;
		case 0xdd:
			key_num = 5;
			break;
		case 0xbd:
			key_num = 6;
			break;
		case 0x7d:
			key_num = 14;
			break;
	 }

	 // thirdrst row check
	 P1 = 0xfb;
	 out = P1;
	 switch(out){
	 	case 0xeb:
			key_num = 1;
			break;
		case 0xdb:
			key_num = 2;
			break;
		case 0xbb:
			key_num = 3;
			break;
		case 0x7b:
			key_num = 13;
			break;
	 }

	 // fourth row check
	 P1 = 0xf7;
	 out = P1;
	 switch(out){
	 	case 0xe7:
			key_num = 0;
			break;
		case 0xd7:
			key_num = 10;
			break;
		case 0xb7:
			key_num = 11;
			break;
		case 0x77:
			key_num = 12;
			break;
	 }
}
void main(void){
	uchar tmp;
	display(0);

	while(1){
		P1 = 0xf0;
		tmp = P1;		
		if ((tmp&0xf0) != 0xf0){
		  // delay to avoid hand shake
		  	delay(10);
		  	P1 = 0xf0;
			tmp = P1;		
			if ((tmp&0xf0) != 0xf0){
				getKeyNum();
			}

			while(tmp!=0xf0){
				 tmp = P1;
				 tmp = tmp&0xf0;
				 display(key_num);
			}
		}

		display(key_num);
	}
}