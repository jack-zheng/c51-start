void Delaynms(unsigned char nms)		//@11.0592MHz
{
	unsigned char i, j;
	while(nms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
	
}
