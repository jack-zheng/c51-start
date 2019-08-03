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
 �ļ���: DS18B20.c
 ����: DS18B20�ɼ��¶Ȳ���ʾ������ܣ�12M�����²�����
 ����:
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#include <reg52.h>
#include <intrins.h>    // ��Ϊ���ļ����õ�����ʱ����_nop_()������Ҫ����_nop_()��ͷ�ļ�

/* ����DS18B20�ӿڶ�Ӧ�Ķ˿� */
//sbit DS18B20_DQ = P1^4; // DS18B20������ͨ������DQ
sbit DQ = P1^4;

/* �����������ʾģ��ӿڶ�Ӧ�Ķ˿� */
sbit DIG_DATA = P0^2;   // 74HC595��������������
sbit DIG_SHCP = P0^4;   // 74HC595����λ��������
sbit DIG_STCP = P2^3;   // 74HC595��������������

/* �������� */
unsigned char DigBuf[4];    //�����������ʾ������

code unsigned char Segment[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; // ���ֶ��룬Segment[0]~Segment[9]�ֱ��Ӧ����0~9�Ķ���
code unsigned char Select[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};       // λѡ��Select[0]Ϊȫѡ��Select[1]~Select[8]�ֱ��Ӧ��1λ�����Ҳࣩ~��8λ������ࣩ

/*---------------------------------------------------------------------------------------------------------*/
/* �¶�ģ��DS18B20��غ��� */
/**********************************************
���ܣ�
    ��ʱ����
���������
    n: ��ʱʱ��
���������
    ��
����ֵ��
**********************************************/
void Delay(unsigned int n)
{
    unsigned int i;
    while(n--)
    {
        i=200;
        while(i--);
    }
}
/*��ʱ��׼3us ����Ϊ11.0592MHz*/
void DelayXus(unsigned char n)
{
    while(n--);
}

void delay4us(unsigned char t){
	while(t--);
}
/**********************************************
���ܣ�
    ��ʼ��DS18B20
���������
    ��
���������
    ��
����ֵ��
**********************************************/
 /*��ʼ�����У�Ŀ���ǿ�һ��DS18B20�Ƿ���ڣ����ڷ���1���������򷵻�0���ý�����һ������*/
void DS18B20Init(void)
{
	// master send a pull down to bus, bus low minimus time is 480 us.
	DQ = 0;
	delay4us(130);
	// then master release bus and wait for slave fead back
	DQ = 1;	
	// after bus released, 18b20 wait 15-60us and give a low signal, 
	delay4us(40);
	// this signal will last about 60-240us, then device release bus
    /* For this practice, ew just think this device would be work, so just delay time and let it go*/
	delay4us(100);
}

/**********************************************
���ܣ�
    дһ���ֽڵ�DS18B20
���������
    WByte:Ҫд���ֽ�
���������
    ��
����ֵ��
**********************************************/
/*дDS18B20һ���ֽ�Byte*/
void DS18B20WriteOneByte(unsigned char cmd)
{
	unsigned char i;

	for (i=0;i<8;i++){
		if (cmd & 0x01){
			// if the bit 0 is high, generate high signal
			// to generate 1 time slot, pull down bus, and release in 15us, all write time slot must be a minimum 60us duration 
			DQ = 0;
			DQ = 1;
			delay4us(30);
		}else{
		 	// to generate 0 time slot, pull down bus and hold at least 60us
			/*hold low for more than 480us will cause all components on bus reset*/
			DQ = 0;
			delay4us(20);
			DQ = 1;	
		}
		cmd >>= 1;
	}	
}
/**********************************************
���ܣ�
    ��DS18B20��ȡһ���ֽ�
���������
    ��
���������
    ��
����ֵ��
    RecByte:��DS18B20����ȡ���ֽ�
**********************************************/
unsigned char DS18B20ReadOneByte(void)
{
	unsigned char dat;
	// all read time slots must be a mininum of 60us in duration with a minimum of 1us recovery time between slots
	unsigned char i;
	for (i=0;i<8;i++){
		// DS18b20 transmit 1 by leave bus to high, and 0 by pull down bus to low till the time slot end.
		dat >>= 1;
		DQ = 0; // bus low as initiates
		DQ = 1;	// reset port and wait for receive
		// data from 18b20 valid for 15us after master's read signal, which mean, *master should finish sample in 15us!*
		if (DQ){
			// if DQ is high, give a 1 to dat
			dat |= 0x80;
		}
		delay4us(30);
	}
	return dat;
}
/**********************************************
���ܣ�
    ��ʼ�¶�ת��
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void DS18B20TConvertStart(void)
{
    DS18B20Init();              //DS18B20��ʼ��
    Delay(1);                   //��ʱ
    
    DS18B20WriteOneByte(0xCC);     //��������ROMָ��
    DS18B20WriteOneByte(0x44);     //���������¶�ת��ָ��
}

/**********************************************
���ܣ�
    ��ȡ�¶�ֵ
���������
    ��
���������
    Temperature: �¶�ֵ��16λ����
    ����BIT15����BIT11(����λ);
        BIT10����BIT4 (����λ);
        BIT3 ����BIT0 (С��λ);
����ֵ��
**********************************************/
unsigned int DS18B20TGet(void)
{
    unsigned int Temperature;
    
    DS18B20Init();              //DS18B20��ʼ��
    Delay(1);                   //��ʱ
    
    DS18B20WriteOneByte(0xCC);     //��������ROMָ��
    DS18B20WriteOneByte(0xBE);     //���Ͷ�ȡ��ǩָ��
    
    Temperature = DS18B20ReadOneByte();    //��ȡ��ǩ�ĵ��ֽڣ�8λ��
    Temperature |= DS18B20ReadOneByte()<<8;//��ȡ��ǩ�ĸ��ֽڣ�8λ��
    
    return(Temperature);        //���ض�ȡ�ı�ǩֵ��16λ��
}

/*---------------------------------------------------------------------------------------------------------*/
/* �������ʾ��غ��� */
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
void DigOutput(unsigned char SelectByte, unsigned char SegmentByte)
{
    unsigned char i;
    
	DIG_SHCP = 0;   // 74HC595����λ������������͵�ƽ
	DIG_STCP = 0;   // 74HC595������������������͵�ƽ
    
    /* �������ֽڣ���8λ����λ��ǰ������74HC595оƬ */
	for(i=0; i<8; i++)
	{
        /* �ж����ݵ����λ��������λ��1��������������ߵ�ƽ�������0������͵�ƽ */
	    if(SegmentByte&0x80)
        {
	        DIG_DATA = 1;
        }
		else
        {
		    DIG_DATA = 0;
        }
		_nop_();
        /* ���74HC595оƬ��������λ���壬ÿ���һ����λ���壬74HC595�ڲ��������ƶ�һλ */
		DIG_SHCP = 1;
		_nop_();
		DIG_SHCP = 0;
		_nop_();
        /* Ҫ�������������һλ����Ϊ��һλ���ݵ������׼�� */
		SegmentByte <<= 1;
	}
    /* ��λѡ�ֽڣ���8λ����λ��ǰ������74HC595оƬ */
	for(i=0; i<8; i++)
	{
	    if(SelectByte&0x80)
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
		SelectByte <<= 1;
	}
    /* ���74HC595оƬ�������������壬����74HC595оƬ���յ����������������оƬ�������������� */
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
void DigShowCustom(unsigned char DigSelect, unsigned char CustomSeg)
{
    if(0<DigSelect<9)   //�ж�λѡ��ֵ�Ƿ�Ϊ1����8�������������Χ�������κβ���
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
void DigShowNumber(unsigned char DigSelect, unsigned char Number, bit Dp)
{
    if((0<DigSelect<9)&&(Number<10))    //ͬʱ�ж�λѡ��ֵ�Ƿ�Ϊ1����8����ʾֵ�Ƿ�Ϊ0����9����������Χ�������κβ���
    {
        if(Dp)
    	{
            DigOutput(Select[DigSelect],(Segment[Number]&~0x80));   //����С����
    	}
    	else
    	{
            DigOutput(Select[DigSelect],(Segment[Number]|0x80));    //Ϩ��С����
    	}
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/**********************************************
    ����������ȡ����ʾDS18B20���¶�
**********************************************/
void main()
{
    unsigned int i=0;   //����ѭ���ļ���ֵ������ʼֵ
    float TGet;         //�����DS18B20��ȡ����
    signed int TShow;   //����ת������Ҫ��ʾ����
    
    while(1)
    {
        /* ����1���������ж���䣬�������¶�ת�� */
        if(i==0)
        {
            DS18B20TConvertStart();     //�����¶�ת��
        }
        /* ����2���������ж���䣬��ȡ�¶�ֵ��ת���洢����ʾ���� */
        if(i==100)
        {
            TGet = DS18B20TGet()*0.0625;//�õ���ʵʮ�����¶�ֵ����ΪDS18B20
        			                    //���Ծ�ȷ��0.0625�ȣ����Զ������ݵ����λ�������0.0625�ȡ�
            TShow = TGet*10+0.5;        //�Ŵ�ʮ������������Ŀ�Ľ�С������һλҲת��Ϊ����ʾ���֣�ͬʱ����һ���������������

            if(TShow<0)                 //�ж��¶�ֵ�Ƿ�Ϊ����
            {
                DigBuf[0] = 0xbf;
                TShow = 0-TShow;
            }
            else
            {
                DigBuf[0] = TShow/1000; //�����¶Ȱ�λֵ
            }
            TShow = TShow%1000;
            DigBuf[1] = TShow/100;      //�����¶�ʮλֵ
            TShow = TShow%100;
            DigBuf[2] = TShow/10;       //�����¶ȸ�λֵ
            DigBuf[3] = TShow%10;       //����С�����һλֵ
        }
        /* ����3����i���м�1����� */
        if(++i>3000)                    //��i��ֵ��1�����ж�i�Ƿ����3000
        {
            i = 0;                      //��������3000�������
        }
        /* ����4����������ܵĶ�̬��ʾ */
        DigShowNumber(1,DigBuf[3],0);   //����ܵ�1λ��ʾС�����һλ��ֵ
        DigShowNumber(2,DigBuf[2],1);   //����ܵ�2λ��ʾ��λֵ��ͬʱ��ʾС����
        DigShowNumber(3,DigBuf[1],0);   //����ܵ�3λ��ʾʮλֵ
        if(DigBuf[0]==0xbf)             //�ж�DigBuf[0]��ֵ�Ƿ�Ϊ0xbf�����ж��¶��Ƿ�Ϊ����
        {
            DigShowCustom(4,0xbf);      //���Ǹ�������4λ��ʾ����
        }
        else if(DigBuf[0]>0)            //��DigBuf[0]��Ϊ0xbf�����ж�DigBuf[0]�Ƿ����0
        {
            DigShowNumber(4,DigBuf[0],0);//��DigBuf[0]����0����4λ��ʾ����ֵ
        }
        else                            //����
        {
            DigShowCustom(4,0xff);      //��4λ�����ȫ��
        }
    }
}