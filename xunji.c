#include "car.h"
#include "Delay.h"
#include <REGX52.H>


//检测到黑线---->1
//未检测黑线--->0
/*
		D1		D2		D3		D4
全为白线	0		0		0		0
黑线偏左	0		1		0		0
黑线偏右	0		0		1		0
直角左拐	1		1		0		0
直角右拐	0		0		1		1


*/

sbit D1 = P3^2;//红外接口
sbit D2 = P3^3;
sbit D3 = P3^4;
sbit D4 = P3^5;

/*void xunji()
{
	unsigned char ct = 2;
	while(ct)
	{
		if (D1 == 1 && D2 == 1 && D3 == 1 && D4 == 1) {
			car_go();//全为黑线，小车直行
		}
		if (D1 == 0 && D2 == 1 && D3 == 0 && D4 == 0) {
			car_leftgo();//黑线偏左，小车左行
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_go();
			}
		}
		if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 0) {
			car_rightgo();//黑线偏右，小车右行
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_go();
			}
		}
		if (D1 == 1 && D2 == 1 && D3 == 0 && D4 == 0) {//直角左拐，小车原地左转
			car_go();
			Delay1ms(50);
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_stop();
				Delay1ms(50);//时间尚未确定，
				car_rightstop();
			}
		}
		if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 1) {		//直角右拐，小车原地右转
			car_go();
			Delay1ms(50);
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_stop();
				Delay1ms(50);
				car_leftstop();
			}
		}
	}
	if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
		car_go();
		Delay1ms(250);
		car_stop();
	}			
	

	
}
*/

void xunji()
{
	unsigned char FSM = 0;//状态机表示状态
	unsigned char ct = 0;//表示转弯次数
	while(1)
	{
		if(FSM == 0)//启动状态
		{
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
			car_go();//未检测到黑线，小车直行
			}
			if (D1 == 0 && D2 == 1 && D3 == 0 && D4 == 0) {
				car_leftgo();//黑线偏左，小车左行
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();
				}
			}
			if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 0) {
				car_rightgo();//黑线偏右，小车右行
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();
				}
			}
			if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 1){//开始转直角弯
				car_go();
				Delay1ms(50);//根据后期实验调整延迟时间
				FSM++;
				continue;
			}
		}
		
		
		if(FSM == 1)//转弯状态
		{
			if(ct < 2){
				if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 1){
					car_rightstop();//一直原地右转
				}
				else if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 0){
					car_rightgo();
					Delay1ms(50);
					FSM++;
					continue;
				}
			}
			if(ct == 2){//进入抓取状态的入口
				FSM = 3;
			}
			if(ct > 2){//进入最后一段直线行驶的入口
				FSM = 5;
			}
		}
		if(FSM == 2)//转弯后的摆动状态
		{
			unsigned char temp = 0;
			while(1){
				if (temp >= 10) break;//temph后期改数据
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();//未检测到黑线，小车直行
					temp++;
				}
				if (D1 == 0 && D2 == 1 && D3 == 0 && D4 == 0) {
					temp = 0;
					car_leftgo();//黑线偏左，小车左行
					if (D1 == 1 && D2 == 1 && D3 == 1 && D4 == 1) {
						car_go();
					}
				}
				if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 1) {
					car_rightgo();//黑线偏右，小车右行
					temp = 0;
					if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
						car_go();
					}
				}
			}
			ct++;
			FSM = 0;
			ct++;
		}
		if(FSM == 3)//实现左转
		{	Delay1ms(50);
			car_leftstop();
			Delay1ms(100);//后期调试到原地左转90
			car_go();
			Delay1ms(100);//后期调试到合适的距离
			FSM++;
		}
		if(FSM == 4)//实现抓取功能
		{
			/*********
			此处实现抓取代码
			**********/
			ct++;
			FSM = 0;
			
			
		}
		if(FSM == 5)//
		{
			car_leftstop();
			Delay1ms(100);//此处调试到原地转弯180
			car_go();
			Delay1ms(100);//此处调试到合适的距离
			FSM++;
		}
		if(FSM == 6)//直线循迹
		{
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_go();//未检测到黑线，小车直行
				break;
			}
			if (D1 == 0 && D2 == 1 && D3 == 0 && D4 == 0) {
				car_leftgo();//黑线偏左，小车左行
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();
				}
			}
			if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 0) {
				car_rightgo();//黑线偏右，小车右行
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();
				}
			}
			Delay1ms(5000);//直线行驶大半距离
			car_go();
			Delay1ms(5000);//后期调试，行驶后半距离
			car_stop();
			FSM++;
		}
		if(FSM == 7)//放下物体
		{
			/************
			此处写放下物体的代码
			**************/
			break;
		}
		
	}
		
}
	
