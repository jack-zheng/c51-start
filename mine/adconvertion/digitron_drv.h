/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: digitron_drv.h
 desc: head file of digital tube driver
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#ifndef __DIGITRON_DRV_H__
#define __DIGITRON_DRV_H__

#include <intrins.h>
#include "type.h"
#include "IO_def.h"

/* Define the data transfer pins of the digitron. */
#define DIG_DATA P02
#define DIG_SHCP P04
#define DIG_STCP P23

/* Define the Interface Functions*/
void DigShowCustom(uint8 DigBit, uint8 CustomSeg);
void DigShowNumber(uint8 DigBit, uint8 Number, bit Dp);
void DigInit(void);

#endif