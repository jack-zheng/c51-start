/*=======================================================
<<<<<<<<<<<<<<<<<<< �����׵¼����Ŷ� >>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<< ����һ��׷��׿Խ >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
�콢����: http://aplid.taobao.com/
�ٷ�����: njaplid@163.com
 ����QQ1: 535676091
 ����QQ2: 1915624375
 ����QQ3: 154211813
---------------------------------------------------------
               All right reserved.2013.01
---------------------------------------------------------
 �ļ���: digitron_drv.h
 ����: �����ģ������ͷ�ļ�
 ����:
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#ifndef __DIGITRON_DRV_H__
#define __DIGITRON_DRV_H__

#include <intrins.h>
#include "type.h"
#include "IO_def.h"

/* ������������ݴ���ӿ�����  Define the data transfer pins of the digitron. */
#define DIG_DATA P02
#define DIG_SHCP P04
#define DIG_STCP P23

/* ����ӿں��� / Define the Interface Functions*/
void DigShowCustom(uint8 DigBit, uint8 CustomSeg);
void DigShowNumber(uint8 DigBit, uint8 Number, bit Dp);
void DigInit(void);

#endif