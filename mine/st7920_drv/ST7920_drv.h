/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: ST7920_drv.h
 desc: head file of LCD12864 display
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#ifndef __LCD12864_DRV_H__
#define __LCD12864_DRV_H__

#include <reg52.h> 
#include "intrins.h" 

void LCD_Init(void);
void LCD_Clear(void);
void DelayMs(unsigned char t);
void LCD_Write_String(unsigned char offset, unsigned char lineNum, unsigned char *str);

#endif