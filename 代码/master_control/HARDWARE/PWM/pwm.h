#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

//ĿǰΪ������Ч���ã��ٶ�����ҪԽ��Խ�õ�
/*
	��ʱ�����PWM������Ϊ�˸�TB6612��PWM����˿��ṩPWM�ź�

	ARR�����ֵΪ 200

	PWMA		TIM1		CH1		PA8			��������������A����PWMA
		TIM_SetCompare1(TIM1,20);
	PWMB		TIM1		CH3		PA10		���������ҵ����B����PWMB
		TIM_SetCompare3(TIM1,20);
*/

void PWM_Init_TIM1(void);


#endif //__MOTOR_H
