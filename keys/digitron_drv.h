/*=======================================================
<<<<<<<<<<<<<<<<<<< 爱普雷德技术团队 >>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<< 我们一起追求卓越 >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
旗舰网店: http://aplid.taobao.com/
官方邮箱: njaplid@163.com
 技术QQ1: 535676091
 技术QQ2: 1915624375
 技术QQ3: 154211813
---------------------------------------------------------
               All right reserved.2013.01
---------------------------------------------------------
 文件名: digitron_drv.h
 描述: 数码管模块驱动头文件
 作者:
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#ifndef __DIGITRON_DRV_H__
#define __DIGITRON_DRV_H__

#include <intrins.h>
#include "type.h"
#include "IO_def.h"

/* 定义数码管数据传输接口引脚  Define the data transfer pins of the digitron. */
#define DIG_DATA P02
#define DIG_SHCP P04
#define DIG_STCP P23

/* 定义接口函数 / Define the Interface Functions*/
void DigShowCustom(uint8 DigBit, uint8 CustomSeg);
void DigShowNumber(uint8 DigBit, uint8 Number, bit Dp);
void DigInit(void);

#endif