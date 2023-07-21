#include "servo.h"


//舵机问题
//		TIM2    CH3 		PA2
//   舵机程序，
void SERVO_PWM_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;				//复用
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;			//推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 199;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8399;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = 10;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);
	//重装载值
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);
}
//左转
void SERVO_Left(void){
	TIM_SetCompare3(TIM2,12);
	delay_ms(1);
}
//居中
void SERVO_Middle(void){
	TIM_SetCompare3(TIM2,15);
	delay_ms(1);
}
//右转
void SERVO_Right(void){
	TIM_SetCompare3(TIM2,18);
	delay_ms(1);
}

