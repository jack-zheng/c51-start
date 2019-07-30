#include <reg52.h>

int count;
sbit led = P1^3;
sbit led1 = P1^1;
sbit led0 = P1^0;
sbit rf = P3^2;

void INT0Config(void)
{
    /*配置外部中断0下降沿触发*/
    IT0 = 1;
   /*中断使能，允许中断发生*/
    EX0 = 1;
    /*优先级默认，不配置*/

    /*开总中断*/
    EA = 1;
}

void delay(){
	unsigned short i,j;
	for(i=0;i<500;i++)
		for(j=0;j<100;j++);
}

void INT0ISR() interrupt 0
{
	led1 = 0;
	 delay();
	 delay();
	 delay();
	 delay();
	 delay();
	 delay();
	 led1 = 1;
}

/*定时器T0配置*/
void Timer0Config(void)
{
    /*选择8位自动重装*/
    TMOD = 0x02;
    /*配置基准时间0.25ms*/
    TH0 = 0x1A;
    TL0 = 0x1A;
    /*启动定时器*/
    TR0 = 1;
    /*开定时器中断*/
    ET0 = 1;

	EA = 1; // enable interrupt
}
/*定时器T0中断响应函数*/
void Timer0ISR() interrupt 1
{
    count ++;
	if(count >= 4000){
		count = 0;
		led = ~led;
	}
}

void main(void){
//	INT0Config();
//	Timer0Config();
//	while(1){
//	led0 = ~led0;
//		 delay();	
//	}
	
	while(1){
		led = rf;
	}

}