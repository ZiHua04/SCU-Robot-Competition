#include <REGX52.H>
#include <intrins.h>
void Delay1ms(unsigned int xms)	//@11.0592MHz
{
	while(xms){
		unsigned char i, j;
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}

