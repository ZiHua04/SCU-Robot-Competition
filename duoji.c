#include <REGX52.H>
#include <intrins.h>

unsigned int count0 = 0;
unsigned int count1 = 0;
unsigned int count2 = 0;
unsigned char timer0;
unsigned char timer1;
unsigned char timer2;
sbit PWM0 = P1^1;
sbit PWM1 = P1^2;
sbit PWM2 = P1^3;



void Timer1_Init()           
{
	TMOD &= 0x0F; //设置计数器1模式
	TMOD |= 0x10; //计数器T1设置成方式1
	TH1 = (65536-100)/256;
	TL1 = (65536-92)%256;
	ET1 = 1; //打开计数器1允许中断
	TR1 = 1; //打开计数器1
	EA = 1; //打开总中断
}

void InterruptTime1() interrupt 3
{
	TR1 = 0;//关闭计数器
    TH1 = (65536-100)/256;
	TL1 = (65536-92)%256;
		
	if(count0 <= timer0) 
	{ 
		PWM0 = 1; 
	}
	else 
	{ 
		PWM0 = 0; 
	}
	if(count1 <= timer1)
	{
		PWM1 = 1;
	}
	else
	{
		PWM1 = 0;
	}
	if(count2 <= timer2)
	{
		PWM2 = 1;
	}
	else
	{
		PWM2 = 0;
	}
	count0++;
	count1++;
	count2++;
	count0 %= 200;
	count1 %= 200;
	count2 %= 200;
	TR1 = 1; //打开计数器1
}
// 左舵机（PWM0）最小1（往下），最大9（往上）
// 右舵机（PWM1）最小1（往回收），最大9（往前伸）
//夹爪舵机（PWM2）9闭合，4张开
void SetTimer(unsigned char x, unsigned char y, unsigned char z)
{
	timer0 = x;
	timer1 = y;
	timer2 = z;
}