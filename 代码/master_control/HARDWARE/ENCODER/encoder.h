#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
/*

	TIM3		PC6		PC7
	TIM4		PD12	PD13
	
	Ϊ������ģʽ		����ģʽ

*/

void Encoder_Init_TIM3(void);
void Encoder_Init_TIM4(void);

int Read_Speed(int TIMx);

#endif 
