#include "timer.h"
//设置一个定时器  ，中断采集数据
/*
TIM5	CH4		PA3
5ms 产生一个中断
*/
void TIMER_Init(void){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	//配置定时器
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频为1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择计数模式为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 49;//（ARR自动重装器的值）----49
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8399;//配置PSC预分频器的值
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	/*4、使能更新中断*/
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//允许定制器5更新中断
	
	/*6、启动定时器*/
	TIM_Cmd(TIM5,ENABLE);
	
	/*5、配置NVIC*/
	//抢占优先级和优先级是数值越小优先级别越高
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;//选择中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//开启中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//响应优先级
	NVIC_Init(&NVIC_InitStructure);	
}

//定时器5中断服务函数
//这个中断函数是为了实现控制的
//用于检测状态是否ok
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{

	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}


/*
//	配置定时中断流程：
//		1.RCC开启时钟（定时器基准时钟和外设工作时钟）
//		2.选择时基单元的时钟源（对于定时中断，选择内部时钟源）
//		3.配置时基单元（包括PSC预分频器，ARR自动重装器，CNT计数器）
//		4.配置输出中断控制，使能更新中断，允许更新中断输出到NVIC
//		5.配置NVIC，打开定时器通道，并分配优先级
//		6.运行控制，使能计数器
*/


