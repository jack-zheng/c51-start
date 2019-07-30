#include <reg52.h>   
#include "LCD1602_drv.h"


sbit IR = P3^2;  //RF sensor port

char code Tab[16] = "0123456789ABCDEF";

unsigned char IrDecodeData[4];
unsigned char PluseTimeData[32];

unsigned char TempData[16];

unsigned char PulseTimeDataPosition;
unsigned char PulseTimeCnt;
unsigned char IrDataFinish;
unsigned char IrDDPosition;


/*32 bit RF signal process*/
void IrDataCopeWith(void)
{ 
	 // the timer is set to 0.25 per loop, we think that, when RF time is between 0.625 - 1.625ms, it's stand to 0 and 1.725msµ½2.725ms as 1
     unsigned char i,j = 0;
     unsigned char byteContainer = 0;
	 unsigned char IrDDPosition = 0; // index of RF code list

     for (i=0;i<32;i++)
     {
             
         if  ((PluseTimeData[i]>=3) &&(PluseTimeData[i]<=6))
         {
              // when it's 0, do nothing
         }
         else
         {
              byteContainer |= 0x80; // the first come in bit is the highest one
         }

         // once 1 byte fill, store it to list, reset index j    
         if (++j >= 8)
         {
             IrDecodeData[IrDDPosition++] = byteContainer;
             byteContainer = 0;
             j = 0;
         }
         
		 // 1 bit move right
         byteContainer  >>= 1;
    }
}


/*------------------------------------------------
                  External Interrupt 0
------------------------------------------------*/
void INT0Config(void)
{
    /*trigger when 1 to 0*/
    IT0 = 1;
   /*enable interrupt*/
    EX0 = 1;

    /*All interrupt enable*/
    EA = 1;
}
/*Logic when EX0 is triggered*/
void INT0ISR() interrupt 0
{
	/* Everytime EX0 triggered, reset time gap counter */
//    PulseTimeCnt = 0; <--- we must put this reset after process it, or logic would be incorrect.
	/*Time gap 10-17ms(40-68 TI), we treat it as RF start signal*/
    if  ((PulseTimeCnt>=40)&(PulseTimeCnt <= 68))
    {
        /* When there is RF signal, start count RF, there are totally 32 bit need to process */
        PulseTimeDataPosition  = 0;
    }
    else
    {
         PluseTimeData[PulseTimeDataPosition++] = PulseTimeCnt;
    }

	PulseTimeCnt = 0;
    if (PulseTimeDataPosition >= 32)
    {
       PulseTimeDataPosition = 0;
       
	   /*After data collection finished, calculate the RF code*/
       IrDataCopeWith();
       /*After process code, set process flag, show result in main func*/
       IrDataFinish = 1;
    }
} 

/*Config T0*/
void Timer0Config(void)
{
    /*8 bit auto reset timer*/
    TMOD = 0x02;
    /*0.25ms per loop*/
    TH0 = 0x1A;
    TL0 = 0x1A;
    /*Start T0*/
    TR0 = 1;
    /*Enable ET0*/
    ET0 = 1;
}
/*Logic when T0 triggered*/
void Timer0ISR() interrupt 1
{
    PulseTimeCnt++;
}



/*------------------------------------------------
                    main func
------------------------------------------------*/
void main (void)
{
    INT0Config();            
    Timer0Config();           

    LCD_Init();           //Init LCD display
    DelayMs(20);          
    LCD_Clear();          //clear display

    LCD_Write_String(0,0,"   TR Project");
    LCD_Write_String(0,1,"IrCode:");
   
   while(1)
   {
       if (IrDataFinish )//RF process flag
       {
            IrDataFinish = 0;
            TempData[0] = Tab[IrDecodeData[2]/16];   //show data of RF code
            TempData[1] = Tab[IrDecodeData[2]%16];
            TempData[2] = '\0';   
            LCD_Write_String(7,1,TempData);//show on LCD1602
       }
   }
}
  
  