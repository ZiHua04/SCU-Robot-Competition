#include <REGX52.H>//����51��Ƭ������ͷ�ļ�

sbit IN11 = P1^1;//
sbit IN12 = P1^2;//
sbit IN13 = P1^4;//
sbit IN14 = P1^3;//
//sbit IN21 = P3^5;//
//sbit IN22 = P3^6;//
//sbit IN23 = P3^3;//
//sbit IN24 = P3^4;//

void LF_go() {
	IN11 = 0;
	IN12 = 1;
}//�������ת
void LF_back() {
	IN11 = 1;
	IN12 = 0;
}//����ﷴת
void LF_stop() {
	IN11 = 1;
	IN12 = 1;
}//�����ͣת
void RF_go() {
	IN13 = 0;
	IN14 = 1;
}//�������ת
void RF_back() {
	IN13 = 1;
	IN14 = 0;
}//����ﷴת
void RF_stop() {
	IN13 = 1;
	IN14 = 1;
}//�����ͣת
//void LB_go() {
//	IN21 = 1;
//	IN22 = 0;
//}
//void LB_back() {
//	IN21 = 0;
//	IN22 = 1;
//}
//void LB_stop() {
//	IN21 = 1;
//	IN22 = 1;
//}
//void RB_go() {
//  IN23 = 1;
//	IN24 = 0;
//}
//void RB_back() {
//	IN23 = 0;
//	IN24 = 1;
//}
//void RB_stop() {
//	IN23 = 1;
//	IN24 = 1;
//}

