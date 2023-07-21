#include "uart4.h"
//用来接收openmv传来的路口的信息
//当接受为'P'时进行下一个路口的转向
extern uint8_t* point;		//用来缓存当前接收到的openmv的信息
extern char* current;//当前的方向
extern char* follow; //下一个的方向

int count = 2;
//point 的比较值
/*
C:路口
S:直行
L:偏左
R:偏右
*/

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟 打开串口外设的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//使能USART1时钟
	
	//串口4对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10复用为UART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11复用为UART4
	
	// uart4的端口配置
	 GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN | DEBUG_USART_RX_GPIO_PIN; //GPIOC10与GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);		

  // 清除发送完成标志
	//USART_ClearFlag(USART1, USART_FLAG_TC);     
}

/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


//接收处理
//openmv----32
// 串口中断服务函数
void DEBUG_USART_IRQHandler(void)
{
	char* ret;
  uint8_t ucTemp;		//接收到的缓冲中间值
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{
		LED1 = !LED1;	//LED的闪烁表示接受一次数据
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
		point = &ucTemp;			//接收到的信息
		
		OLED_ShowString(56,32,point,16,1);  //串的值-- 最底下
		
		//路口的反馈是-- PALR
		//其余的反馈是-- N
		if(strcmp((char*)point,"C") == 0){			//接收到一个路口的信息
			if((count % 2) == 0){
				
				ret = direction(current,follow);
				Usart_SendString(UART4,ret);//反馈信号  //发送信息给openmv一个反馈
				current = follow;
				//follow = a[i++];
				follow = getNextCmd();//获取到下一次的节点
				if(strcmp(ret,"A") == 0){
					count++;
					Usart_SendByte(UART4,'B');
				}
			}
			//直行后没有C
			else if((count % 2) ==1){
				Usart_SendByte(UART4,'B');
			}
			OLED_ShowString(86,48,"C",16,1);
			OLED_Refresh();
			count++;
		}
		//等待传入直行的信号
		else if(strcmp((char*)point,"S") == 0){
			OLED_ShowString(86,48,"S",16,1);
			OLED_Refresh();
			moto_advance();
			Usart_SendByte(UART4,'N');
		}
		else if(strcmp((char*)point,"N") == 0){   //空白地段
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
		
		OLED_ShowString(0,0,current,16,1);			//最上面
		OLED_ShowString(56,0,follow,16,1);
		
		*point = 0;
		OLED_Refresh();//刷新
	}
}

