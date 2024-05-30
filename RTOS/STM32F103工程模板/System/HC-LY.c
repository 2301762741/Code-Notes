#include "stm32f10x.h"                  // Device header
#include "System.h"
#include "string.h"

uint8_t HC_RxSTA;   //标志位
//char ZxData[100];   //数据缓存


void HCint()
{
	USEint();  //串口初始化 
	
	GPint(GPC,OutPP,P15);  //控制灯口初始化
	GPIO_SetBits(GC,P15);//LED1_OFF();
	
//	/*******************OLED显示模块************************/
//	OLED_Init();
//	OLED_ShowString(1,1,"SEND:");
//	OLED_ShowString(3,1,"RECV:");
}


/**
  * 函    数：实现指令
  * 参    数：字符串指令
  * 功    能：操作对应功能 
  */
uint8_t HC_Orde(char *Buf)
{
	static uint8_t mode=0;
	if (HC_RxSTA == 1 )		//如果接收到数据包
	{
			mode=0;
			OLED_Clear_Part(1,1,16);    //初始化屏幕
			OLED_ShowString(1, 1, "MIND:");
			
			/*将收到的数据包与预设的指令对比，以此决定将要执行的操作*/
			if(Buf[0] == '@')     //是否为指令判断
			{
					if (strcmp(Buf, "@LED_ON") == 0)			//如果收到LED_ON指令
					{
						GPIO_ResetBits(GC,P15);//LED1_ON();										//点亮LED
						USE_SendString("LED_ON_OK\r\n");				//串口回传一个字符串LED_ON_OK
						OLED_Clear_Part(2,1,16);
						OLED_ShowString(2, 1, "LED_ON_OK");				//OLED清除指定位置，并显示LED_ON_OK
					}
					else if (strcmp(Buf, "@LED_OFF") == 0)	//如果收到LED_OFF指令
					{
						GPIO_SetBits(GC,P15);//LED1_OFF();										//熄灭LED
						USE_SendString("LED_OFF_OK\r\n");			//串口回传一个字符串LED_OFF_OK
						OLED_Clear_Part(2,1,16);
						OLED_ShowString(2, 1, "LED_OFF_OK");			//OLED清除指定位置，并显示LED_OFF_OK
					}
					else if (strcmp(Buf, "@Music") == 0)	//如果收到LED_HUXI指令
					{
																//熄灭LED
						USE_SendString("Music_OK\r\n");			//串口回传一个字符串Music_OK
						OLED_Clear_Part(2,1,16);
						OLED_ShowString(2, 1, "Music_OK");			//OLED清除指定位置，并显示Music_OK
						Music();
					}
					else if (strcmp(Buf, "@MODE_1") == 0)	//如果收到LED_HUXI指令
					{
						mode=1;//LED1_OFF();										//熄灭LED
						USE_SendString("MODE_1_OK\r\n");			//串口回传一个字符串LED_OFF_OK
						OLED_Clear_Part(2,1,16);
						OLED_ShowString(2, 1, "MODE_1_OK");			//OLED清除指定位置，并显示LED_OFF_OK
					}
					else						//上述所有条件均不满足，即收到了未知指令
					{
						USE_SendString("ERROR_COMMAND\r\n");			//串口回传一个字符串ERROR_COMMAND		
						OLED_Clear_Part(2,1,16);
						OLED_ShowString(2, 1, "ERROR_COMMAND");			//OLED清除指定位置，并显示ERROR_COMMAND
					}
			}
			else
					OLED_Clear_Part(2,1,16),
					OLED_ShowString(2,1,"NONE");  //返回不是指令的提示
				
			/*MY*/strcpy(Buf, "");      //清理内容 
			HC_RxSTA = 0;			//处理完成后，需要将接收数据包标志位清零，否则将无法接收后续数据包
			}
		return mode;
}

/**
  * 函    数：发送数据
  * 参    数：string字符串
  * 参    数：... 可变的参数列表
  * 返 回 值：无
  */
void HC_SendString(char *Buf)
{
	USE_Printf(Buf);
}

/**
  * 函    数：接收数据
  * 参    数：存放数据的缓存
  * 参    数：字符数组
  * 返 回 值：无 ，注意接受数组的函数要清除标志位和BUF
  */
void HC_GetData(char *Buf)
{
	uint32_t count = 0, a = 0;
	while (count < 10000)
	{
		if (USE_GetRxFlag() == 1)
		{
			Buf[a] = USE_RxData;
			a ++;
			count = 0;
			HC_RxSTA = 1;        //读到数据后置标志位为1 
		}
		count ++;
	}
	Buf[a]='\0';            //添加结束位，否则数据会重复
	
	if (HC_RxSTA)
	{
			OLED_Clear_Part(4,1,16);
			OLED_ShowString(4, 1, Buf);  //打印数据包
	}
//	static uint8_t RxState = 0;		//定义表示当前状态机状态的静态变量
//	static uint8_t pRxPacket = 0;	//定义表示当前接收数据位置的静态变量
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)	//判断是否是USART1的接收事件触发的中断
//	{
//		uint8_t RxData = USE_RxData;			//读取数据寄存器，存放在接收的数据变量
//		
//		/*使用状态机的思路，依次处理数据包的不同部分*/
//		
//		/*当前状态为0，接收数据包包头*/
//		if (RxState == 0)
//		{
//			if (RxData == '@' && HC_RxSTA == 0)		//如果数据确实是包头，并且上一个数据包已处理完毕
//			{
//				RxState = 1;			//置下一个状态
//				pRxPacket = 0;			//数据包的位置归零
//			}
//		}
//		/*当前状态为1，接收数据包数据，同时判断是否接收到了第一个包尾*/
//		else if (RxState == 1)
//		{
//			if (RxData == '\r')			//如果收到第一个包尾
//			{
//				RxState = 2;			//置下一个状态
//			}
//			else						//接收到了正常的数据
//			{
//				Buf[pRxPacket] = RxData;		//将数据存入数据包  数组的指定位置
//				pRxPacket ++;			//数据包的位置自增
//			}
//		}
//		/*当前状态为2，接收数据包第二个包尾*/
//		else if (RxState == 2)
//		{
//			if (RxData == '\n')			//如果收到第二个包尾
//			{
//				RxState = 0;			//状态归0
//				Buf[pRxPacket-1] = '\0';			//将收到的字符数据包添加一个字符串结束标志
//        OLED_ShowString(4,1,ZxData);
//				HC_RxSTA = 1;		//接收数据包标志位置1，成功接收一个数据包
//			}
//		}
//		
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除标志位
//	}
}


/**
  * 函    数：USART1中断发送数据包函数
  * 参    数：无
	* 返 回 值:   应用状态机USE_RxPacket可以组成个字符串来显示
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
//void USART1_IRQHandler(void)       //此函数使用状态机处理标志位，使用请清理前面的USE_GetRxFlag函数
//{
//	static uint8_t RxState = 0;		//定义表示当前状态机状态的静态变量
//	static uint8_t pRxPacket = 0;	//定义表示当前接收数据位置的静态变量
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)	//判断是否是USART1的接收事件触发的中断
//	{
//		uint8_t RxData = USART_ReceiveData(USART1);			//读取数据寄存器，存放在接收的数据变量
//		
//		/*使用状态机的思路，依次处理数据包的不同部分*/
//		
//		/*当前状态为0，接收数据包包头*/
//		if (RxState == 0)
//		{
//			if (RxData == '@' && HC_RxSTA == 0)		//如果数据确实是包头，并且上一个数据包已处理完毕
//			{
//				RxState = 1;			//置下一个状态
//				pRxPacket = 0;			//数据包的位置归零
//			}
//		}
//		/*当前状态为1，接收数据包数据，同时判断是否接收到了第一个包尾*/
//		else if (RxState == 1)
//		{
//			if (RxData == '\r')			//如果收到第一个包尾
//			{
//				RxState = 2;			//置下一个状态
//			}
//			else						//接收到了正常的数据
//			{
//				ZxData[pRxPacket] = RxData;		//将数据存入数据包  数组的指定位置
//				pRxPacket ++;			//数据包的位置自增
//			}
//		}
//		/*当前状态为2，接收数据包第二个包尾*/
//		else if (RxState == 2)
//		{
//			if (RxData == '\n')			//如果收到第二个包尾
//			{
//				RxState = 0;			//状态归0
//				ZxData[pRxPacket] = '\0';			//将收到的字符数据包添加一个字符串结束标志
//        OLED_ShowString(4,1,ZxData);
//				HC_RxSTA = 1;		//接收数据包标志位置1，成功接收一个数据包
//			}
//		}
//		
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除标志位
//	}
//}
