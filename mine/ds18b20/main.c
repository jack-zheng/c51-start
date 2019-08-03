#include <reg52.h>
#include <digitron_drv.h>

sbit DQ = P1^4;

/*Time delay, expected time should be t*4us*/
void delay4us(unsigned char t){
	while(t--);
}

/*write 8 byte data to ROM*/
void writeByte(unsigned char cmd){
	unsigned char i;

	for (i=0;i<8;i++){
		if (cmd & 0x01){
			// if the bit 0 is high, generate high signal
			// to generate 1 time slot, pull down bus, and release in 15us，
			// all write time slot must be a minimum 60us duration 
			DQ = 0;
			DQ = 1;
			delay4us(30);
		}else{
		 	// to generate 0 time slot, pull down bus and hold at least 60us
			/*hold low for more than 480us will cause all components on bus reset*/
			DQ = 0;
			delay4us(30);
			DQ = 1;	
		}
		cmd >>= 1;
	}	
}

unsigned char readByte(void){
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

void init(void){
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

void delay1s(){
	unsigned short int i,j;
	for (i=0;i<500;i++)
		for(j=0;j<200;j++);
}

void main(void){

	unsigned char step;
	unsigned int tmp;
	unsigned char digBuf[3];
	unsigned int cnt;
	
	   
	while(1){

		switch(step){
			case 0:
				init();

				// give a sign to start convert
				// give a time delay to wait for time conversion, it should be about 1s 
				writeByte(0xcc); // skip rom command
				writeByte(0x44);
				step = 1;
				break;
			case 1: // wait for tmp trasfer
				// 1s delay to temp convertion
				if(cnt++>2000){
					step = 2;
					cnt = 0;
				}

				break;
			case 2:
				init();
				delay4us(1);
				writeByte(0xcc);
				writeByte(0xbe);
		
				tmp = readByte();
				tmp |= readByte()<<8;
		
				tmp = tmp*0.625;
		
				//tmp = tmp*50/8; when put *5*10 together, number is too large
				
				digBuf[0] = tmp/100;
				tmp = tmp%100;
				digBuf[1] = tmp/10;
				digBuf[2] = tmp%10;	 
				step = 0;
				break;
			default:
				break;

		} 

		DigShowNumber(1, digBuf[2], FALSE);
		DigShowNumber(2, digBuf[1], TRUE);
		DigShowNumber(3, digBuf[0], FALSE);
	}	  
}										