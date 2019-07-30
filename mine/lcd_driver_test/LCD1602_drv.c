/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: LCD1602_drv.c
 desc: driver of LCD1602 display
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#include "LCD1602_drv.h"

sbit RS = P2^7;   //定义液晶控制端口
sbit RW = P2^6;
sbit EN = P2^5;

#define CHECK_BUSY

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

#define DataPort P0


/**********************************************
desc:
    (2*x + 5) us time delay
params:
    delayms: time to delay, the delay time nearly equals	 
	to 'delayus * 2 + 5' us
return:
    void
**********************************************/
void DelayUs2x(unsigned char delayus)
{   
    while(--delayus);
}

/**********************************************
desc:
    T ms time delay
params:
    time to delay
return:
    void
**********************************************/
void DelayMs(unsigned char t)
{
     
    while(t--)
    {
         // nearly 1ms delay
         DelayUs2x(245);
         DelayUs2x(245);
    }
}

/**********************************************
desc:
    Check if display is busy
params:
   	none
return:
    void
**********************************************/
bit LCD_Check_Busy(void) 
{ 
    #ifdef CHECK_BUSY
    DataPort= 0xFF; 
    RS_CLR; 
    RW_SET; 
    EN_CLR; 
    _nop_(); 
    EN_SET;
    return (bit)(DataPort & 0x80);
}

/**********************************************
desc:
    Write data to instruction register
params:
   	command to write
return:
    void
**********************************************/
void LCD_Write_Com(unsigned char com) 
{  
    while(LCD_Check_Busy()); //wait till device not busy
    RS_CLR; 
    RW_CLR; 
    EN_SET; 
    DataPort= com; 
    _nop_(); 
    EN_CLR;
}

/**********************************************
desc:
    Write data to data register
params:
   	data to write
return:
    void
**********************************************/
void LCD_Write_Data(unsigned char Data) 
{ 
    while(LCD_Check_Busy()); //wait till device not busy
    RS_SET; 
    RW_CLR; 
    EN_SET; 
    DataPort= Data; 
    _nop_();
    EN_CLR;
}

/**********************************************
desc:
    Clear display
params:
   	none
return:
    void
**********************************************/
void LCD_Clear(void) 
{ 
    LCD_Write_Com(0x01); 
    DelayMs(5);
}

/**********************************************
desc:
    Write string data to display
params:
	offset, the position offset from the start position
   	lineNum, which line to write, 0 to write the first line, other to wirte the second line
	str, content to write
return:
    void
**********************************************/
void LCD_Write_String(unsigned char offset, unsigned char lineNum, unsigned char *str)
{     
    if (lineNum == 0) 
    {     
        LCD_Write_Com(0x80 + offset);     //write the first line
    }
    else 
    {      
        LCD_Write_Com(0xC0 + offset);      //write the second line
    }    
    while(*str != '\0') //loop till the string end
    {
        LCD_Write_Data( *str);     
        str ++;
    }
}

/**********************************************
desc:
    Init display
params:
	none
return:
    void
**********************************************/
void LCD_Init(void) 
{
   LCD_Write_Com(0x38);    /*set display mode*/ 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*turn off display*/ 
   LCD_Write_Com(0x01);    /*clear display*/ 
   LCD_Write_Com(0x06);    /*cursor setting*/ 
   DelayMs(5); 
   LCD_Write_Com(0x0C);    /*turn on display and set cursor*/
}