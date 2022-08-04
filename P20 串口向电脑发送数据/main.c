#include <REGX52.H>
#include "UART.h"

void main()
{
	UART_Init();
	UART_Send(0xFF);
	while(1);
}