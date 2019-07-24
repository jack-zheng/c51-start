#include <reg52.h>
sbit relay=P3^3;

void delay(){
	unsigned int i, j;
	for(i=10;i<100;i++){
		for(j=0;j<100;j++){}
	}
}

void main(void){
	while(1){
		relay = 1;
		delay();
		relay = 0;
		delay();
	}
}