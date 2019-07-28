/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: IIC_drv.
 desc: head file of IIC protocal
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/


#include <reg52.h>
#include <intrins.h>

sbit Scl = P2^1;	//clock port of AT24C02
sbit Sda = P2^0;	//data port of AT24C02

void WriteIIC(unsigned char device,unsigned char address,unsigned char temp);
unsigned char ReadIIC(unsigned char device,unsigned char address);

