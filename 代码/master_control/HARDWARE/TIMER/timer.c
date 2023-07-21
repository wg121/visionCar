#include "timer.h"
//����һ����ʱ��  ���жϲɼ�����
/*
TIM5	CH4		PA3
5ms ����һ���ж�
*/
void TIMER_Init(void){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	//���ö�ʱ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�ƵΪ1��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//ѡ�����ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 49;//��ARR�Զ���װ����ֵ��----49
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8399;//����PSCԤ��Ƶ����ֵ
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	/*4��ʹ�ܸ����ж�*/
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);//��������5�����ж�
	
	/*6��������ʱ��*/
	TIM_Cmd(TIM5,ENABLE);
	
	/*5������NVIC*/
	//��ռ���ȼ������ȼ�����ֵԽС���ȼ���Խ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;//ѡ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�����ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructure);	
}

//��ʱ��5�жϷ�����
//����жϺ�����Ϊ��ʵ�ֿ��Ƶ�
//���ڼ��״̬�Ƿ�ok
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{

	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}


/*
//	���ö�ʱ�ж����̣�
//		1.RCC����ʱ�ӣ���ʱ����׼ʱ�Ӻ����蹤��ʱ�ӣ�
//		2.ѡ��ʱ����Ԫ��ʱ��Դ�����ڶ�ʱ�жϣ�ѡ���ڲ�ʱ��Դ��
//		3.����ʱ����Ԫ������PSCԤ��Ƶ����ARR�Զ���װ����CNT��������
//		4.��������жϿ��ƣ�ʹ�ܸ����жϣ���������ж������NVIC
//		5.����NVIC���򿪶�ʱ��ͨ�������������ȼ�
//		6.���п��ƣ�ʹ�ܼ�����
*/


