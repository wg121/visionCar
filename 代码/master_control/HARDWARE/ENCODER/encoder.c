#include "encoder.h"
//编码器电机
/*

	TIM3		PC6	 （A相）	PC7  （B相）			--左编码器电机的码盘
	TIM4		PD12 （A相）	PD13 （B相）    	--有编码器电机的码盘

*/
//TIM3		PC6	 （A相）	PC7  （B相）			--左编码器电机的码盘
void Encoder_Init_TIM3(){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;//中断
	
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
	TIM_TimeBaseInitStruct.TIM_Period = 65535;		//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;			//预分频
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising); // 这里配置了编码器模式

	TIM_ICStructInit(&TIM_ICInitStructure);//  初始化输入捕获   缺省输入
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;  //选择输入端IC1映射到TI1上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  //上升沿捕获
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//不分频
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;		//映射到TI1上
	TIM_ICInitStructure.TIM_ICFilter = 10; // 这里可以自己设置，或使用默认值    滤波器设置
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;		//选择输入端IC1映射到TI2上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//映射到TI2上
	TIM_ICInitStructure.TIM_ICFilter = 10; // 这里可以自己设置，或使用默认值    滤波器设置
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                   //定时器3中断分组配置
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                   //使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;      //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x02;            //响应优先级2
	NVIC_Init(&NVIC_InitStructure);                                 //配置定时器3
		
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);		//清楚溢出更新中断标志位
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//配置溢出更新标志位
	
	TIM_SetCounter(TIM3, 0);
	TIM_Cmd(TIM3, ENABLE);			//使能定时器三
}

void Encoder_Init_TIM4(){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;//中断
	
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
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising); // 这里配置了编码器模式

	TIM_ICStructInit(&TIM_ICInitStructure);//初始化输入捕获
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;  //选择输入端IC1映射到TI1上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  //上升沿捕获
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//不分频
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;		//映射到TI1上
	TIM_ICInitStructure.TIM_ICFilter = 10; // 这里可以自己设置，或使用默认值    滤波器设置
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;		//选择输入端IC1映射到TI2上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//映射到TI2上
	TIM_ICInitStructure.TIM_ICFilter = 10; // 这里可以自己设置，或使用默认值    滤波器设置
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;                   //定时器4中断分组配置
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                   //使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;      //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x02;            //响应优先级2
	NVIC_Init(&NVIC_InitStructure);                                 //配置定时器3
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);		//清楚溢出更新中断标志位
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//配置溢出更新标志位
	
	TIM_SetCounter(TIM4, 0);
	TIM_Cmd(TIM4, ENABLE);	//使能
}


/*
 *编码器速递读取函数
 *入口参数：定时器
 * 参数为：3 或者 4
*/
int Read_Speed(int TIMx){     //读取编码器速度
	int value_1;
	switch(TIMx){
		case 3:value_1=(short)TIM_GetCounter(TIM3);TIM_SetCounter(TIM3,0);break;   //定时器2，  首先采集编码器的计数值并保存，然后将计数器清零
		case 4:value_1=(short)TIM_GetCounter(TIM4);TIM_SetCounter(TIM4,0);break;   //定时器4
		default:value_1=0;
	}
	return value_1;
}

void TIM3_IRQHandler(void){   //定时器3中断
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != 0){
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void){   //定时器4中断
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != 0){
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}


