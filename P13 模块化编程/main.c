#include <REGX52.H>
#include "Nixie.h"

void main() {

	while(1)
	{
		SegmentDisplay(0x80, 1);
		SegmentDisplay(0x40, 2);
		SegmentDisplay(0x20, 3);
	}
}