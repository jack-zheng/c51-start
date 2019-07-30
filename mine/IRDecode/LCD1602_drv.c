#include "LCD1602_drv.h"
/*>>>>>>>>>>>>>>>>>>>>>>>>>Һ��������ʼ>>>>>>>>>>>>>>>>>>>>>>*/

sbit RS = P2^7;   //����Һ�����ƶ˿�
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


/*------------------------------------------------
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
    while(--t);
}
/*------------------------------------------------
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
    while(t--)
    {
         //������ʱ1mS
         DelayUs2x(245);
         DelayUs2x(245);
    }
}

/*------------------------------------------------
              ��æ����
------------------------------------------------*/
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
    #else
    return 0;
    #endif
}
/*------------------------------------------------
              д�������
-----------------   ----------------------------*/
void LCD_Write_Com(unsigned char com) 
{  
    while(LCD_Check_Busy()); //æ��ȴ�
    RS_CLR; 
    RW_CLR; 
    EN_SET; 
    DataPort= com; 
    _nop_(); 
    EN_CLR;
}
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
void LCD_Write_Data(unsigned char Data) 
{ 
    while(LCD_Check_Busy()); //æ��ȴ�
    RS_SET; 
    RW_CLR; 
    EN_SET; 
    DataPort= Data; 
    _nop_();
    EN_CLR;
}

/*------------------------------------------------
                ��������
------------------------------------------------*/
void LCD_Clear(void) 
{ 
    LCD_Write_Com(0x01); 
    DelayMs(5);
}
/*------------------------------------------------
              д���ַ�������
------------------------------------------------*/
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s)
{     
    if (y == 0) 
    {     
        LCD_Write_Com(0x80 + x);     //��ʾ��һ��
    }
    else 
    {      
        LCD_Write_Com(0xC0 + x);      //��ʾ�ڶ���
    }    
    while(*s != '\0') //�ַ���β��
    {
        LCD_Write_Data( *s);     
        s ++;
    }
}

/*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
void LCD_Init(void) 
{
   LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*��ʾ�ر�*/ 
   LCD_Write_Com(0x01);    /*��ʾ����*/ 
   LCD_Write_Com(0x06);    /*��ʾ����ƶ�����*/ 
   DelayMs(5); 
   LCD_Write_Com(0x0C);    /*��ʾ�����������*/
}

/*>>>>>>>>>>>>>>>>>>>>>>>>>Һ����������>>>>>>>>>>>>>>>>>>>>>>*/