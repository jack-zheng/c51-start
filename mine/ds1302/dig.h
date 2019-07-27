#ifndef __DIG_H__
#define __DIG_H__

#include "reg52.h"

sbit dig_data = P0^2;
sbit shcp = P0^4;
sbit stcp = P2^3;

extern unsigned char pos[];
extern unsigned char num[];

void showNumber(unsigned char num, unsigned char pos);
void display(unsigned char val);
#endif