#include "uart4.h"
//��������openmv������·�ڵ���Ϣ
//������Ϊ'P'ʱ������һ��·�ڵ�ת��
extern uint8_t* point;		//�������浱ǰ���յ���openmv����Ϣ
extern char* current;//��ǰ�ķ���
extern char* follow; //��һ���ķ���

int count = 2;
//point �ıȽ�ֵ
/*
C:·��
S:ֱ��
L:ƫ��
R:ƫ��
*/

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ�� �򿪴��������ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��USART1ʱ��
	
	//����4��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10����ΪUART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11����ΪUART4
	
	// uart4�Ķ˿�����
	 GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN | DEBUG_USART_RX_GPIO_PIN; //GPIOC10��GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);		

  // ���������ɱ�־
	//USART_ClearFlag(USART1, USART_FLAG_TC);     
}

/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


//���մ���
//openmv----32
// �����жϷ�����
void DEBUG_USART_IRQHandler(void)
{
	char* ret;
  uint8_t ucTemp;		//���յ��Ļ����м�ֵ
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{
		LED1 = !LED1;	//LED����˸��ʾ����һ������
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
		point = &ucTemp;			//���յ�����Ϣ
		
		OLED_ShowString(56,32,point,16,1);  //����ֵ-- �����
		
		//·�ڵķ�����-- PALR
		//����ķ�����-- N
		if(strcmp((char*)point,"C") == 0){			//���յ�һ��·�ڵ���Ϣ
			if((count % 2) == 0){
				
				ret = direction(current,follow);
				Usart_SendString(UART4,ret);//�����ź�  //������Ϣ��openmvһ������
				current = follow;
				//follow = a[i++];
				follow = getNextCmd();//��ȡ����һ�εĽڵ�
				if(strcmp(ret,"A") == 0){
					count++;
					Usart_SendByte(UART4,'B');
				}
			}
			//ֱ�к�û��C
			else if((count % 2) ==1){
				Usart_SendByte(UART4,'B');
			}
			OLED_ShowString(86,48,"C",16,1);
			OLED_Refresh();
			count++;
		}
		//�ȴ�����ֱ�е��ź�
		else if(strcmp((char*)point,"S") == 0){
			OLED_ShowString(86,48,"S",16,1);
			OLED_Refresh();
			moto_advance();
			Usart_SendByte(UART4,'N');
		}
		else if(strcmp((char*)point,"N") == 0){   //�հ׵ض�
			OLED_ShowString(86,48,"N",16,1);
			OLED_Refresh();
			Usart_SendByte(UART4,'N');
		}
		else if(strcmp((char*)point,"L") == 0){
			OLED_ShowString(86,48,"L",16,1);
			OLED_Refresh();
			moto_small_left();
			Usart_SendByte(UART4,'N');
		}
		
		else if(strcmp((char*)point,"R") == 0){
			OLED_ShowString(86,48,"R",16,1);
			OLED_Refresh();
			moto_small_right();
			Usart_SendByte(UART4,'N');
		}
		
		OLED_ShowString(0,0,current,16,1);			//������
		OLED_ShowString(56,0,follow,16,1);
		
		*point = 0;
		OLED_Refresh();//ˢ��
	}
}

