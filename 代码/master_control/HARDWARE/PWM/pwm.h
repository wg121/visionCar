#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

//目前为了做的效果好，速度是需要越慢越好的
/*
	定时器输出PWM波，是为了给TB6612的PWM输入端口提供PWM信号

	ARR的最大值为 200

	PWMA		TIM1		CH1		PA8			用来控制左电机（A）的PWMA
		TIM_SetCompare1(TIM1,20);
	PWMB		TIM1		CH3		PA10		用来控制右电机（B）的PWMB
		TIM_SetCompare3(TIM1,20);
*/

void PWM_Init_TIM1(void);


#endif //__MOTOR_H
