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
 �ļ���: digitron_drv.c
 ����: �����ģ������c�ļ�
 ����:
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#include "digitron_drv.h"

code uint8 Segment[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
code uint8 Select[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

/**********************************************
���ܣ�
    ���λѡ�ֽںͶ����ֽ�
���������
    SelectByte:  λѡ�ֽ�
    SegmentByte: �����ֽ�
���������
    ��
����ֵ��
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
���ܣ�
    ��ĳλ��ʾ�Զ������
���������
    DigSelect: �����λѡ��1����8�������ҵ�����
    CustomSeg: �Զ������ֵ
���������
    ��
����ֵ��
**********************************************/
void DigShowCustom(uint8 DigSelect, uint8 CustomSeg)
{
    if(0<DigSelect<9)
    {
        DigOutput(Select[DigSelect],CustomSeg);
    }
}

/**********************************************
���ܣ�
    ��ĳλ��ʾ����
���������
    DigSelect: �����λѡ��1����8�������ҵ�����
    Number:    ���֣�0����9��
    Dp:        С���㣨1:��ʾ��0:����ʾ��
���������
    ��
����ֵ��
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
���ܣ�
    ��ʼ������ܣ�ʹ�����ȫ��
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void DigInit(void)
{
    DIG_DATA = 0;
	DIG_SHCP = 0;
	DIG_STCP = 0;
    DigOutput(0x00,0xff);
}