#include <REGX52.H>
#include <Timer0.h>
#include <Key.h>
#include <Nixie.h>

unsigned char KeyNum,Min,Sec,MiniSec;
unsigned char RunFlag=1;

void main()
{
	Timer0_Init();

	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			RunFlag=!RunFlag;
		}
		if(KeyNum==2)
		{
			Min=0;Sec=0;MiniSec=0;
		}
		// 显示秒表界面
		Nixie_SetBuf(1,Min/10);
		Nixie_SetBuf(2,Min%10);
		Nixie_SetBuf(3,11);
		Nixie_SetBuf(4,Sec/10);
		Nixie_SetBuf(5,Sec%10);
		Nixie_SetBuf(6,11);
		Nixie_SetBuf(7,MiniSec/10);
		Nixie_SetBuf(8,MiniSec%10);
	}
}

void Sec_Loop()
{
	if(RunFlag)	// 只有当Flag为1时，计数
	{
		MiniSec++;
		if(MiniSec>=100)
		{
			MiniSec=0;
			Sec++;
			if(Sec>=60)
			{
				Sec=0;
				Min++;
				if(Min>=60)
				{
					Min=0;
				}
			}
		}
	}
}

/**
  * @brief 这个函数还有提升的空间，我们可以把按键和数码管的逻辑移动到Timer1中，减小对计时的影响
  * @param 
  * @retval 
  */
void Timer0_Rountine() interrupt 1
{
	// 中断计数器
	static unsigned int KeyCount,NixieCount,SecCount;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	KeyCount++;
	if(KeyCount>=20)
	{
		KeyCount=0;	// 重置计数器
		Key_Loop();	// 每20ms扫描一次按键
	}
	
	NixieCount++;
	if(NixieCount>=2)
	{
		NixieCount=0;	// 重置计数器
		Nixie_Loop();	// 每2ms扫描一次按键
	}
	
	SecCount++;
	if(SecCount>=10)
	{
		SecCount=0;
		Sec_Loop();
	}
}
