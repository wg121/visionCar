#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"

/*
		per = 199				arr
		psc = 8399

		TIM2    CH3 		PA2

�Ƕ�ֵ��
		5				0
		10			45
		15			90
		20			135
		25			180
*/


/*
����ĽǶȿ��ƣ�
TIM_SetCompare3(TIM2,10);//���
TIM_SetCompare3(TIM2,15);//�м�
TIM_SetCompare3(TIM2,20);//�ұ�
*/

void SERVO_PWM_Init(void);

void SERVO_Left(void);
void SERVO_Middle(void);
void SERVO_Right(void);



#endif   // __DERVO_H
