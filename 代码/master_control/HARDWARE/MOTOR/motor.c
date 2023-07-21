#include "motor.h"
//���---tb6612
/*
	���������4��io��
	PF->0 1 2 3 
	
	TIM1	CH1		����	
	TIM1	CH4		����
*/

void MOTO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); /*����GPIOB������ʱ��*/

  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;		/*ѡ��Ҫ���Ƶ�����*/   
																																										// 2����� ��4��IO��	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //����:����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;      //����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 	/*������������Ϊ100MHz*/ 

	GPIO_Init(GPIOF, &GPIO_InitStructure);		 	/*���ÿ⺯������ʼ��*/		 
	GPIO_SetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);		//����͵�ƽ---Ϊ���ǳ�ʼ����ʱ�������Ӳ���
}
//ǰ��
void moto_advance(void){
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 1; 
	BIN2 = 0;
	TIM_SetCompare1(TIM1,45);   //	PWMA
	TIM_SetCompare4(TIM1,45);   //  PWMB
	
	TIM_SetCompare3(TIM2,15);
	OLED_ShowChinese(64,16,8,16,1);		//OLED��ʾǰ��
	OLED_ShowChinese(80,16,9,16,1);
	OLED_Refresh();		//ˢ��oled
}
//��ת
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
	OLED_Refresh();		//ˢ��oled
}
//΢���Ƕ�
void moto_small_left(void){
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 1;
	BIN2 = 0;
	TIM_SetCompare1(TIM1,10);		//	PWMA----���
	TIM_SetCompare4(TIM1,45);		//
}

//��ת
void moto_right(void){
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 0;
	BIN2 = 0;
	TIM_SetCompare1(TIM1,45);
	TIM_SetCompare4(TIM1,10);
	
	TIM_SetCompare3(TIM2,18);
	OLED_ShowChinese(64,16,12,16,1);		//OLED��ʾ��ת
	OLED_ShowChinese(80,16,13,16,1);
	OLED_Refresh();		//ˢ��oled
}
//΢���Ƕ�
void moto_small_right(void){
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 1;
	BIN2 = 0;
	TIM_SetCompare1(TIM1,45);		//	PWMA----���
	TIM_SetCompare4(TIM1,10);		//
}

//����
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
	OLED_Refresh();		//ˢ��oled
}
//ֹͣ
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
	OLED_Refresh();		//ˢ��oled
}
