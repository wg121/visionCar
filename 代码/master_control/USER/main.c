#include "sys.h"

//主函数的控制文件，
/*
up			北
down		南
left
right
over
*/
char* current;//当前的方向
char* follow; //下一个的方向
uint8_t* point;		//用来缓存当前接收到的openmv的信息

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//第二组
	delay_init(168);
	LED_Init();  					//LED灯  检验--LED1--5ms定时器检查
	OLED_Init();					//OLED显示
	//showtitle();				//oled显示标题
	
	OLED_ShowString(0,32,"point:",16,1);
	OLED_ShowString(0,48,"IR_get:",16,1);
	
	TIMER_Init();					//定时器5做处理，定时器中断
	SERVO_PWM_Init();			//舵机，车头部分
	
	MOTO_Init();						//电机初始化
	PWM_Init_TIM1();				//PWM信号
	Encoder_Init_TIM3();		//编码器电机初始化
	Encoder_Init_TIM4();	
	
	USART_Config();					//串口4的初始化
	
	moto_stop();						//初始化让小车不动
	
	follow = getNextCmd();//获取到下一次的
	current = follow;
	follow = getNextCmd();//获取到下一次的节点
	while(1){
		
	//走一格大概是需要5秒
		LED0 = 0;	//LED0 亮：表示路段信息获取完成
	}
}

