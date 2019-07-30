#include <reg52.h>

int count;
sbit led = P1^3;
sbit led1 = P1^1;
sbit led0 = P1^0;
sbit rf = P3^2;

void INT0Config(void)
{
    /*�����ⲿ�ж�0�½��ش���*/
    IT0 = 1;
   /*�ж�ʹ�ܣ������жϷ���*/
    EX0 = 1;
    /*���ȼ�Ĭ�ϣ�������*/

    /*�����ж�*/
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

/*��ʱ��T0����*/
void Timer0Config(void)
{
    /*ѡ��8λ�Զ���װ*/
    TMOD = 0x02;
    /*���û�׼ʱ��0.25ms*/
    TH0 = 0x1A;
    TL0 = 0x1A;
    /*������ʱ��*/
    TR0 = 1;
    /*����ʱ���ж�*/
    ET0 = 1;

	EA = 1; // enable interrupt
}
/*��ʱ��T0�ж���Ӧ����*/
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