#include "Timer0.h"
#include <REGX52.H>
#include "car.h"
#include "xunji.h"
#include "Delay.h"
#include "duoji.h"

sbit D1 = P2^2;
sbit D2 = P2^1;
void main()
{
	Timer0_Init();
	Timer1_Init();
	while(1)
	{
		signed char i;
		for(i = 1; i < 10; i++)
		{
			SetTimer(i,0,0);
			Delay1ms(5);
			if(i == 1) Delay1ms(10);
		}
	}
//	Timer1_Init();
//	while(1)
//	{
//		if(D1 == 0 && D2 == 0)  // ?????????????,??
//        {
//            car_go();
//        }
//        else if(D1 == 1 && D2 == 0)  // ???????????,????
//        {
//			car_leftgo();
//		   if(D1 == 0 && D2 == 0)
//		   {
//			   car_go();
//		   }
//        }
//        else if(D1 == 0 && D2 == 1)  // ???????????,????
//        {
//            car_rightgo();
//		   if(D1 == 0 && D2 == 0)
//		   {
//			   car_go();
//		   }
//        }
//        else  // ???????????????,??
//        {
//            car_stop();
//        }
//	}
}



 












