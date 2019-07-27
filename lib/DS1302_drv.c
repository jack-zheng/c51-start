/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: DS1302_drv.c
 desc: driver of DS1302
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#include "DS1302_drv.h"

/**********************************************
desc:
    send byte to DS1302
params:
    TByte:the byte to send
return:
    void
**********************************************/
static void TransmitByte(uint8 TByte)
{
    uint8 i;
    for(i = 0;i < 8;i++)
    {
		DS1302_CLK = 0;
        if(TByte&0x01)
        {
            DS1302_IO = 1;
        }
        else
        {
            DS1302_IO = 0;
        }
        DS1302_CLK = 1;
        TByte >>= 1;
    }
}

/**********************************************
desc:
    receive a byte from DS1302
params:
    none
return:
    the time data transfer from DS1302
**********************************************/
static uint8 ReceiveByte(void)
{
    uint8 i,RecByte;
    for(i = 0;i < 8;i++)
    {
		DS1302_CLK = 0;
        RecByte >>= 1;
        if(DS1302_IO)
        {
            RecByte |= 0x80;
        }
        else
        {
            RecByte &= ~0x80;
        }
        DS1302_CLK = 1;
    }
    return(RecByte);
}

/**********************************************
desc:
    write byte data to some address of DS1302
params:
    Adr£ºregister address of DS1302
    WByte£ºthe value to be written
return:
    void
**********************************************/
void WriteDS1302(uint8 Adr, uint8 WByte)
{
	DS1302_RST = 0;  
	DS1302_CLK = 0;  
	DS1302_RST = 1;  
 	TransmitByte(Adr); 
	TransmitByte(WByte);
	DS1302_RST = 0;
}


/**********************************************
desc:
    read time from DS1302
params:
    Adr£ºthe time register to be read
return:
    the time value of register
**********************************************/
uint8 ReadDS1302(uint8 Adr)
{
	unsigned char RByte;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	TransmitByte(Adr);
	RByte = ReceiveByte();
	DS1302_RST = 0;
	return(RByte);
}
