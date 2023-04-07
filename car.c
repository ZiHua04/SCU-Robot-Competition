#include "motor.h"
#include "Delay.h"
#include <REGX52.H>
#include "Timer0.h"

sbit EN1A = P1^0;//L298n��ʹ�ܽӿ�
sbit EN1B = P1^5;
//sbit EN2A = P3^7;//��һ����L298n�����ӿ�
//sbit EN2B = P3^2;

static unsigned char counter0,speed;//speed�����ٶ�

void car_go() {//С��ֱ��
	speed = 20;
	LF_go();
	RF_go();
}

void car_back() {//С������
	speed = 20;
	LF_back();
	RF_back();
}

void car_stop() {//С��ֹͣ
	speed = 0;
	LF_stop();
	RF_stop();
}

void car_rightgo() {//С�����ҹ�
	speed = 20;
	RF_stop();
	LF_go();
}

void car_leftgo() {//С�������
	speed = 15;
	RF_go();
	LF_stop();
}

void car_rightback() {//С�����Һ���
	speed = 20;
	LF_back();
	RF_stop();
}

void car_leftback() {//С���������
	speed = 20;
	LF_stop();
	RF_back();
}

void car_rightstop() {//С��ԭ����ת
	speed = 20;
	LF_go();
	RF_back();
}

void car_leftstop() {//С��ԭ����ת
	speed = 20;
	LF_back();
	RF_go();
}

void Timer0_Routine () interrupt 1
{
	TR0 = 0;
	TL0 = 0x9C;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	counter0++;
	counter0 %= 100;
	if(counter0 < speed)
	{
		EN1A = 1;
		EN1B = 1;
//		EN2A = 1;
//		EN2B = 1;
	}
	else
	{
		EN1A = 0;
		EN1B = 0;
//		EN2A = 0;
//		EN2B = 0;
	}
	TR0 = 1;
}