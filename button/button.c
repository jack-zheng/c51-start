# include <reg52.h>
sbit key_left = P1^0;
sbit led = P1^4;

void main(void){
	unsigned char keyStep = 0;
	unsigned short int keyDelay = 0;
	while(1){
		 switch(keyStep){
		 	case 0:
				if(!key_left){
					keyDelay = 0;
					keyStep = 1;
				}
				break;
			case 1:	 // time delay to avoid shake
				if(keyDelay++>1000){
					keyStep = 2;
				}
				break;
			case 2: // double check if button pushed
				if (!key_left){
					led=~led;
					keyStep = 3;
				}else{
					keyStep = 0;
				}
				break;
			case 3: // after button reset, reset keyStep
				if (key_left){
					keyStep = 0;
				}
				break;
		 	default:
				break;
		 }
	}
}