#include "sys.h"

//�������Ŀ����ļ���
/*
up			��
down		��
left
right
over
*/
char* current;//��ǰ�ķ���
char* follow; //��һ���ķ���
uint8_t* point;		//�������浱ǰ���յ���openmv����Ϣ

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ڶ���
	delay_init(168);
	LED_Init();  					//LED��  ����--LED1--5ms��ʱ�����
	OLED_Init();					//OLED��ʾ
	//showtitle();				//oled��ʾ����
	
	OLED_ShowString(0,32,"point:",16,1);
	OLED_ShowString(0,48,"IR_get:",16,1);
	
	TIMER_Init();					//��ʱ��5��������ʱ���ж�
	SERVO_PWM_Init();			//�������ͷ����
	
	MOTO_Init();						//�����ʼ��
	PWM_Init_TIM1();				//PWM�ź�
	Encoder_Init_TIM3();		//�����������ʼ��
	Encoder_Init_TIM4();	
	
	USART_Config();					//����4�ĳ�ʼ��
	
	moto_stop();						//��ʼ����С������
	
	follow = getNextCmd();//��ȡ����һ�ε�
	current = follow;
	follow = getNextCmd();//��ȡ����һ�εĽڵ�
	while(1){
		
	//��һ��������Ҫ5��
		LED0 = 0;	//LED0 ������ʾ·����Ϣ��ȡ���
	}
}

