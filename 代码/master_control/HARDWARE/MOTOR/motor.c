#include "motor.h"
//电机---tb6612
/*
	两个电机，4个io口
	PF->0 1 2 3 
	
	TIM1	CH1		左轮	
	TIM1	CH4		右轮
*/

void MOTO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); /*开启GPIOB的外设时钟*/

  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;		/*选择要控制的引脚*/   
																																										// 2个电机 ，4个IO口	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //类型:推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;      //下拉
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 	/*设置引脚速率为100MHz*/ 

	GPIO_Init(GPIOF, &GPIO_InitStructure);		 	/*调用库函数，初始化*/		 
	GPIO_SetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);		//输出低电平---为的是初始化的时候让轮子不动
}
//前进
void moto_advance(void){
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 1; 
	BIN2 = 0;
	TIM_SetCompare1(TIM1,45);   //	PWMA
	TIM_SetCompare4(TIM1,45);   //  PWMB
	
	TIM_SetCompare3(TIM2,15);
	OLED_ShowChinese(64,16,8,16,1);		//OLED显示前进
	OLED_ShowChinese(80,16,9,16,1);
	OLED_Refresh();		//刷新oled
}
//左转
void moto_left(void){
	AIN1 = 0;
	AIN2 = 0;
	BIN1 = 1;
	BIN2 = 0;
	TIM_SetCompare1(TIM1,10);///	PWM
	TIM_SetCompare4(TIM1,45);
	
	TIM_SetCompare3(TIM2,12);
	OLED_ShowChinese(64,16,10,16,1);//OLED
	OLED_ShowChinese(80,16,11,16,1);
	OLED_Refresh();		//刷新oled
}
//微调角度
void moto_small_left(void){
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 1;
	BIN2 = 0;
	TIM_SetCompare1(TIM1,10);		//	PWMA----左边
	TIM_SetCompare4(TIM1,45);		//
}

//右转
void moto_right(void){
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 0;
	BIN2 = 0;
	TIM_SetCompare1(TIM1,45);
	TIM_SetCompare4(TIM1,10);
	
	TIM_SetCompare3(TIM2,18);
	OLED_ShowChinese(64,16,12,16,1);		//OLED显示左转
	OLED_ShowChinese(80,16,13,16,1);
	OLED_Refresh();		//刷新oled
}
//微调角度
void moto_small_right(void){
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 1;
	BIN2 = 0;
	TIM_SetCompare1(TIM1,45);		//	PWMA----左边
	TIM_SetCompare4(TIM1,10);		//
}

//后退
void moto_back(void){
	AIN1 = 0;
	AIN2 = 1;
	BIN1 = 0;
	BIN2 = 1;
	TIM_SetCompare1(TIM1,45);   //	PWMA
	TIM_SetCompare4(TIM1,45);   //  PWMB
	SERVO_Middle();
	OLED_ShowChinese(64,16,16,16,1);
	OLED_ShowChinese(80,16,17,16,1);
	OLED_Refresh();		//刷新oled
}
//停止
void moto_stop(void){
	AIN1 = 0;
	AIN2 = 0;
	BIN1 = 0;
	BIN2 = 0;
	TIM_SetCompare1(TIM1,0);   //	PWMA
	TIM_SetCompare4(TIM1,0);   //  PWMB
	TIM_SetCompare3(TIM2,15);
	OLED_ShowChinese(64,16,14,16,1);
	OLED_ShowChinese(80,16,15,16,1);
	OLED_Refresh();		//刷新oled
}
