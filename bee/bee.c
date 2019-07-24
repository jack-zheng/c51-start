#include <reg52.h>
sbit bee = P3^4;

void delay(){
	unsigned int i,j;
	for(i=0;i<100;i++){
		for(j=0;j<100;j++){}
	}
}

void main(void){
	while(1){
		bee = 1;
		delay();
		bee = 0;
		delay();
	}
}