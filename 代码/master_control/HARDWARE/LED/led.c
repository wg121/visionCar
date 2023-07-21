#include "led.h"

void LED_Init(void){
	GPIO_InitTypeDef LED_GPIO_Def;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	LED_GPIO_Def.GPIO_Mode = GPIO_Mode_OUT;     //模式
	LED_GPIO_Def.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; 
	LED_GPIO_Def.GPIO_OType = GPIO_OType_PP;    //类型
	
	LED_GPIO_Def.GPIO_PuPd = GPIO_PuPd_UP;      //上下拉
	LED_GPIO_Def.GPIO_Speed = GPIO_Speed_50MHz;  //速度
	
	GPIO_Init(GPIOF,&LED_GPIO_Def);
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);	//拉高电平，输出1，led0，led1灭
}


