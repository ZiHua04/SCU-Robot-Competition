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
	TMOD &= 0x0F; //���ü�����1ģʽ
	TMOD |= 0x10; //������T1���óɷ�ʽ1
	TH1 = (65536-100)/256;
	TL1 = (65536-92)%256;
	ET1 = 1; //�򿪼�����1�����ж�
	TR1 = 1; //�򿪼�����1
	EA = 1; //�����ж�
}

void InterruptTime1() interrupt 3
{
	TR1 = 0;//�رռ�����
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
	TR1 = 1; //�򿪼�����1
}
// ������PWM0����С1�����£������9�����ϣ�
// �Ҷ����PWM1����С1�������գ������9����ǰ�죩
//��צ�����PWM2��9�պϣ�4�ſ�
void SetTimer(unsigned char x, unsigned char y, unsigned char z)
{
	timer0 = x;
	timer1 = y;
	timer2 = z;
}