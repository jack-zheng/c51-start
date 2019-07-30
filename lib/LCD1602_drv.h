/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: LCD1602_drv.h
 desc: head file of LCD1602 display
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#ifndef __LCD1602_DRV_H__
#define __LCD1602_DRV_H__

#include <reg52.h> 
#include "intrins.h" 

void LCD_Init(void);
void LCD_Clear(void);
void DelayMs(unsigned char t);
void LCD_Write_String(unsigned char offset, unsigned char lineNum, unsigned char *str);

#endif