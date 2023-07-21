#include "encoder.h"
//���������
/*

	TIM3		PC6	 ��A�ࣩ	PC7  ��B�ࣩ			--����������������
	TIM4		PD12 ��A�ࣩ	PD13 ��B�ࣩ    	--�б��������������

*/
//TIM3		PC6	 ��A�ࣩ	PC7  ��B�ࣩ			--����������������
void Encoder_Init_TIM3(){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;//�ж�
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65535;		//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;			//Ԥ��Ƶ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising); // ���������˱�����ģʽ

	TIM_ICStructInit(&TIM_ICInitStructure);//  ��ʼ�����벶��   ȱʡ����
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;  //ѡ�������IC1ӳ�䵽TI1��
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  //�����ز���
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//����Ƶ
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;		//ӳ�䵽TI1��
	TIM_ICInitStructure.TIM_ICFilter = 10; // ��������Լ����ã���ʹ��Ĭ��ֵ    �˲�������
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;		//ѡ�������IC1ӳ�䵽TI2��
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//ӳ�䵽TI2��
	TIM_ICInitStructure.TIM_ICFilter = 10; // ��������Լ����ã���ʹ��Ĭ��ֵ    �˲�������
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                   //��ʱ��3�жϷ�������
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                   //ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;      //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x02;            //��Ӧ���ȼ�2
	NVIC_Init(&NVIC_InitStructure);                                 //���ö�ʱ��3
		
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);		//�����������жϱ�־λ
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//����������±�־λ
	
	TIM_SetCounter(TIM3, 0);
	TIM_Cmd(TIM3, ENABLE);			//ʹ�ܶ�ʱ����
}

void Encoder_Init_TIM4(){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;//�ж�
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct); 
	
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising); // ���������˱�����ģʽ

	TIM_ICStructInit(&TIM_ICInitStructure);//��ʼ�����벶��
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;  //ѡ�������IC1ӳ�䵽TI1��
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  //�����ز���
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//����Ƶ
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;		//ӳ�䵽TI1��
	TIM_ICInitStructure.TIM_ICFilter = 10; // ��������Լ����ã���ʹ��Ĭ��ֵ    �˲�������
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;		//ѡ�������IC1ӳ�䵽TI2��
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//ӳ�䵽TI2��
	TIM_ICInitStructure.TIM_ICFilter = 10; // ��������Լ����ã���ʹ��Ĭ��ֵ    �˲�������
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;                   //��ʱ��4�жϷ�������
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                   //ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;      //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x02;            //��Ӧ���ȼ�2
	NVIC_Init(&NVIC_InitStructure);                                 //���ö�ʱ��3
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);		//�����������жϱ�־λ
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//����������±�־λ
	
	TIM_SetCounter(TIM4, 0);
	TIM_Cmd(TIM4, ENABLE);	//ʹ��
}


/*
 *�������ٵݶ�ȡ����
 *��ڲ�������ʱ��
 * ����Ϊ��3 ���� 4
*/
int Read_Speed(int TIMx){     //��ȡ�������ٶ�
	int value_1;
	switch(TIMx){
		case 3:value_1=(short)TIM_GetCounter(TIM3);TIM_SetCounter(TIM3,0);break;   //��ʱ��2��  ���Ȳɼ��������ļ���ֵ�����棬Ȼ�󽫼���������
		case 4:value_1=(short)TIM_GetCounter(TIM4);TIM_SetCounter(TIM4,0);break;   //��ʱ��4
		default:value_1=0;
	}
	return value_1;
}

void TIM3_IRQHandler(void){   //��ʱ��3�ж�
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != 0){
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void){   //��ʱ��4�ж�
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != 0){
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}


