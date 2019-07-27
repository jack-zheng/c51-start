/*=======================================================
<<<<<<<<<<<<<<<<<<< Collect By Jack >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
---------------------------------------------------------
               All right reserved.2019.07
---------------------------------------------------------
 file name: digitron_drv.c
 desc: driver of ditital tube
 author: ?
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#include "digitron_drv.h"

code uint8 Segment[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
code uint8 Select[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

/**********************************************
desc:
    Select digital tube and show number on it
params:
    SelectByte:  choice which tube to turn on
    SegmentByte: show number on tube
return:
    void
**********************************************/
static void DigOutput(uint8 SelectByte, uint8 SegmentByte)
{
    uint8 i;
    
	DIG_SHCP = 0;
	DIG_STCP = 0;

	for(i=0; i<8; i++)
	{
	    if(SegmentByte&0x80)
        {
	        DIG_DATA = 1;
        }
		else
        {
		    DIG_DATA = 0;
        }
		_nop_();
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
		SegmentByte <<= 1;
	}
	for(i=0; i<8; i++)
	{
	    if(SelectByte&0x80)
	        DIG_DATA = 1;
		else
		    DIG_DATA = 0;
		_nop_();
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
		SelectByte <<= 1;
	}
	DIG_STCP = 1;
	_nop_();
	DIG_STCP = 0;
	_nop_();
}

/**********************************************
desc:
    Turn on digital tube of special
params:
    DigSelect: position number, from 1 to 8 mean right to left
    CustomSeg: number to show, hex format
return:
    void
**********************************************/
void DigShowCustom(uint8 DigSelect, uint8 CustomSeg)
{
    if(0<DigSelect<9)
    {
        DigOutput(Select[DigSelect],CustomSeg);
    }
}

/**********************************************
desc:
    turn on digital tube of special
params:
    DigSelect: position number, from 1 to 8 mean right to left
    Number: show numer to tube, number is 0-9
	Dp: if turn point
return:
    void
**********************************************/
void DigShowNumber(uint8 DigSelect, uint8 Number, bit Dp)
{
    if((0<DigSelect<9)&&(Number<10))
    {
        if(Dp)
    	{
            DigOutput(Select[DigSelect],(Segment[Number]&~0x80));
    	}
    	else
    	{
            DigOutput(Select[DigSelect],(Segment[Number]|0x80));
    	}
    }
}


/**********************************************
desc:
    init digital tube, and turn off them all
params:
	none
return:
    void
**********************************************/
void DigInit(void)
{
    DIG_DATA = 0;
	DIG_SHCP = 0;
	DIG_STCP = 0;
    DigOutput(0x00,0xff);
}