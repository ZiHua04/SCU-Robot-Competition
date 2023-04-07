#include "car.h"
#include "Delay.h"
#include <REGX52.H>


//��⵽����---->1
//δ������--->0
/*
		D1		D2		D3		D4
ȫΪ����	0		0		0		0
����ƫ��	0		1		0		0
����ƫ��	0		0		1		0
ֱ�����	1		1		0		0
ֱ���ҹ�	0		0		1		1


*/

sbit D1 = P3^2;//����ӿ�
sbit D2 = P3^3;
sbit D3 = P3^4;
sbit D4 = P3^5;

/*void xunji()
{
	unsigned char ct = 2;
	while(ct)
	{
		if (D1 == 1 && D2 == 1 && D3 == 1 && D4 == 1) {
			car_go();//ȫΪ���ߣ�С��ֱ��
		}
		if (D1 == 0 && D2 == 1 && D3 == 0 && D4 == 0) {
			car_leftgo();//����ƫ��С������
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_go();
			}
		}
		if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 0) {
			car_rightgo();//����ƫ�ң�С������
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_go();
			}
		}
		if (D1 == 1 && D2 == 1 && D3 == 0 && D4 == 0) {//ֱ����գ�С��ԭ����ת
			car_go();
			Delay1ms(50);
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_stop();
				Delay1ms(50);//ʱ����δȷ����
				car_rightstop();
			}
		}
		if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 1) {		//ֱ���ҹգ�С��ԭ����ת
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
	unsigned char FSM = 0;//״̬����ʾ״̬
	unsigned char ct = 0;//��ʾת�����
	while(1)
	{
		if(FSM == 0)//����״̬
		{
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
			car_go();//δ��⵽���ߣ�С��ֱ��
			}
			if (D1 == 0 && D2 == 1 && D3 == 0 && D4 == 0) {
				car_leftgo();//����ƫ��С������
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();
				}
			}
			if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 0) {
				car_rightgo();//����ƫ�ң�С������
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();
				}
			}
			if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 1){//��ʼתֱ����
				car_go();
				Delay1ms(50);//���ݺ���ʵ������ӳ�ʱ��
				FSM++;
				continue;
			}
		}
		
		
		if(FSM == 1)//ת��״̬
		{
			if(ct < 2){
				if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 1){
					car_rightstop();//һֱԭ����ת
				}
				else if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 0){
					car_rightgo();
					Delay1ms(50);
					FSM++;
					continue;
				}
			}
			if(ct == 2){//����ץȡ״̬�����
				FSM = 3;
			}
			if(ct > 2){//�������һ��ֱ����ʻ�����
				FSM = 5;
			}
		}
		if(FSM == 2)//ת���İڶ�״̬
		{
			unsigned char temp = 0;
			while(1){
				if (temp >= 10) break;//temph���ڸ�����
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();//δ��⵽���ߣ�С��ֱ��
					temp++;
				}
				if (D1 == 0 && D2 == 1 && D3 == 0 && D4 == 0) {
					temp = 0;
					car_leftgo();//����ƫ��С������
					if (D1 == 1 && D2 == 1 && D3 == 1 && D4 == 1) {
						car_go();
					}
				}
				if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 1) {
					car_rightgo();//����ƫ�ң�С������
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
		if(FSM == 3)//ʵ����ת
		{	Delay1ms(50);
			car_leftstop();
			Delay1ms(100);//���ڵ��Ե�ԭ����ת90
			car_go();
			Delay1ms(100);//���ڵ��Ե����ʵľ���
			FSM++;
		}
		if(FSM == 4)//ʵ��ץȡ����
		{
			/*********
			�˴�ʵ��ץȡ����
			**********/
			ct++;
			FSM = 0;
			
			
		}
		if(FSM == 5)//
		{
			car_leftstop();
			Delay1ms(100);//�˴����Ե�ԭ��ת��180
			car_go();
			Delay1ms(100);//�˴����Ե����ʵľ���
			FSM++;
		}
		if(FSM == 6)//ֱ��ѭ��
		{
			if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
				car_go();//δ��⵽���ߣ�С��ֱ��
				break;
			}
			if (D1 == 0 && D2 == 1 && D3 == 0 && D4 == 0) {
				car_leftgo();//����ƫ��С������
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();
				}
			}
			if (D1 == 0 && D2 == 0 && D3 == 1 && D4 == 0) {
				car_rightgo();//����ƫ�ң�С������
				if (D1 == 0 && D2 == 0 && D3 == 0 && D4 == 0) {
					car_go();
				}
			}
			Delay1ms(5000);//ֱ����ʻ������
			car_go();
			Delay1ms(5000);//���ڵ��ԣ���ʻ������
			car_stop();
			FSM++;
		}
		if(FSM == 7)//��������
		{
			/************
			�˴�д��������Ĵ���
			**************/
			break;
		}
		
	}
		
}
	
