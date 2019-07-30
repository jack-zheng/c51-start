#include <reg52.h>
#include "LCD1602_drv.h"

void main(void){
	LCD_Init();
	DelayMs(20);
	LCD_Clear();

	LCD_Write_String(0, 1, "Mother Fucker!!!");
	while(1);
}