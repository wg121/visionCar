#include "pwm.h"
//pwm�ź�
/*
	��ʱ�����PWM������Ϊ�˸�TB6612��PWM����˿��ṩPWM�ź�

	PWMA		TIM1		CH1		PA8
	PWMB		TIM1		CH4		PA11
*/
void PWM_Init_TIM1(void){

	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//���ó�ʼ����ʱ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 199;					//per----ARR	�������ڣ�ARR�Զ���װ��ֵ��
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8399;			//psc					Ԥ��Ƶ����ֵ
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	//����PWM����
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_Pulse = 10;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);
	TIM_OC4Init(TIM1,&TIM_OCInitStruct);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	//ʹ��Ԥװ�ؼĴ���������λ
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	//������ʱ��
	TIM_Cmd(TIM1,ENABLE);
}
