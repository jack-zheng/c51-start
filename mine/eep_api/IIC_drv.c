/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: IIC_drv.c
 desc: driver of IIC protocal
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#include "IIC_drv.h"

/**********************************************
desc:
    start communication
params:
    none
return:
    void
**********************************************/
static void Start(void)
{
	Sda = 1;
	Scl = 1;
	Sda = 0;
}

/**********************************************
desc:
    stop communication
params:
    none
return:
    void
**********************************************/
static void Stop(void)
{
	Sda = 0;
	Scl = 1;
	Sda = 1;
}

/**********************************************
desc:
    check if response feed back from device
params:
	none
return:
	if response give back
	1 for yes and 0 for no
**********************************************/
static unsigned char Respons(void)
{
	unsigned char OverTime = 0;  
	unsigned char TempFlag = 0;
	OverTime = 0;
    Sda = 1;     
    Scl = 1;
	while(1)
	{
		if(Sda) 
		{
			if(OverTime++ > 200)
			{
			   TempFlag = 0; 
			   break;
			}
		}
		else
		{
		    TempFlag = 1;   
			break;
		}
	}
	Scl = 0;
	return TempFlag;
}

/**********************************************
desc:
    no acknowledge
params:
    none
return:
	void
**********************************************/
static void NoRespons(void)
{
    Sda = 1;
    Scl = 1;
	Scl = 0;
}

/**********************************************
desc:
    write byte to device
params:
    temp: data to write
return:
    void
**********************************************/
static void WriteByte(unsigned char temp)
{
	unsigned char i;
	Scl = 0;
	for(i = 0;i < 8;i++)
	{
		Sda = temp & 0x80;
		temp <<= 1;
		Scl = 1;
		Scl = 0;
	}
}

/**********************************************
desc:
    read byte
params:
   	none
return:
    the readed byte value
**********************************************/
static unsigned char ReadByte(void)
{
	unsigned char i;
	unsigned char ret = 0;
	for(i = 0;i < 8;i++)
	{
		Scl = 1;
		ret <<= 1;
		ret |= (unsigned char)Sda;
		Scl = 0;	
	}
	return ret;
}

/**********************************************
desc:
    write data to device
params:
    device:		device address
    parameter: address to write data
    temp:     data to write
return:
    void
**********************************************/
void WriteIIC(unsigned char device,unsigned char parameter,unsigned char temp)
{
	Start();
	WriteByte(device);
	if(Respons())
	{
		WriteByte(parameter);
		if(Respons())
		{
			WriteByte(temp);
			if(Respons())
			{
				Stop();
			}
			else
			{
				Stop();
			}
		}
		else
		{
			Stop();
		}
	}
	else
	{
		Stop();
	}
}

/**********************************************
desc:
    read data from chip
params:¡êo
    device:   device address
    parameter:	data address
return:
    the readed byte value
**********************************************/
unsigned char ReadIIC(unsigned char device,unsigned char parameter)
{
	unsigned char ret;
	Start();
	WriteByte(device);
	if(Respons())
	{
		WriteByte(parameter);
		if(Respons())
		{
			Start();
			WriteByte(device | 0x01);
			if(Respons())
			{
				ret = ReadByte();
				NoRespons();
				Stop();
			}
			else
			{
				Stop();
			}
		}
		else
		{
			Stop();
		}
	}
	else
	{
		Stop();
	}
	return ret;
}

	

