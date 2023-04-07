#include "motor.h"
#include "Delay.h"
#include <REGX52.H>
#include "Timer0.h"

sbit EN1A = P1^0;//L298n的使能接口
sbit EN1B = P1^5;
//sbit EN2A = P3^7;//另一个的L298n两个接口
//sbit EN2B = P3^2;

static unsigned char counter0,speed;//speed代表速度

void car_go() {//小车直行
	speed = 20;
	LF_go();
	RF_go();
}

void car_back() {//小车后退
	speed = 20;
	LF_back();
	RF_back();
}

void car_stop() {//小车停止
	speed = 0;
	LF_stop();
	RF_stop();
}

void car_rightgo() {//小车向右拐
	speed = 20;
	RF_stop();
	LF_go();
}

void car_leftgo() {//小车向左拐
	speed = 15;
	RF_go();
	LF_stop();
}

void car_rightback() {//小车向右后退
	speed = 20;
	LF_back();
	RF_stop();
}

void car_leftback() {//小车向左后退
	speed = 20;
	LF_stop();
	RF_back();
}

void car_rightstop() {//小车原地右转
	speed = 20;
	LF_go();
	RF_back();
}

void car_leftstop() {//小车原地左转
	speed = 20;
	LF_back();
	RF_go();
}

void Timer0_Routine () interrupt 1
{
	TR0 = 0;
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
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