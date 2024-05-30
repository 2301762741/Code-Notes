#include "stm32f10x.h"                  // Device header
#include "System.h"

#define GPIOk RCC_APB2Periph_GPIOB
#define EXpin GPIO_Pin_15    
#define EXTI_Tri EXTI_Trigger_Falling   //中断触发模式选择

#define EXlin EXpin    //两个宏定义0~15线路大体参数相同可复用
//此外还需要改下对应的中断函数名

uint16_t CountSensor_Count;				//全局变量，用于计数
/**
  * 函    数：开n方计算函数，用于EXpin与GPIO_PortSource的转换
  * 参    数：传入计算值，开方的底数
  * 返 回 值：能被n开放的次数
  */
uint32_t sqort(uint32_t arm,uint8_t gen)
{
	uint32_t count=0;
	while(arm/gen)
		arm/=gen,
		count++;
	
	return count;
}

/**
  * 函    数：中断初始化
  * 参    数：无
  * 返 回 值：无
  */
void EXTIint(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(GPIOk, ENABLE);		//开启GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启AFIO的时钟，外部中断必须开启AFIO的时钟，AFIO复用选择外设用于选择中断引脚
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = EXpin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	SW_GPIOi(GPIOk, &GPIO_InitStructure);						//将PB14引脚初始化为上拉输入
	
	//AFIO选择中断引脚
	uint8_t GPIO_PortSource;
	switch(GPIOk)
	{
		case RCC_APB2Periph_GPIOA: 
					GPIO_PortSource=GPIO_PortSourceGPIOA;break;
		case RCC_APB2Periph_GPIOB:
					GPIO_PortSource=GPIO_PortSourceGPIOB;break;
		case RCC_APB2Periph_GPIOC:
					GPIO_PortSource=GPIO_PortSourceGPIOC;break;
	}
	GPIO_EXTILineConfig(GPIO_PortSource, sqort(EXpin,2));//将外部中断的1号线映射到对应GPIO，即选择对应的GPIO_PinSource0~15，原：uint8_t GPIO_PortSource, uint8_t GPIO_PinSource
	
	/*EXTI初始化*/
	EXTI_InitTypeDef EXTI_InitStructure;						//定义结构体变量
	EXTI_InitStructure.EXTI_Line = EXlin;					//选择配置外部中断的14号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Tri ;		//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置NVIC为分组2
																//即抢占优先级范围：0~3，响应优先级范围：0~3
																//此分组配置在整个工程中仅需调用一次
																//若有多个中断，可以把此代码放在main函数内，while循环之前
																//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
}


/**
  * 函    数：中断处理操作的函数
  * 参    数：无
  * 返 回 值：无
  */
uint16_t EXTI_Get(void)
{
	GPint(GPA,OutPP,P11);
	if(GPIO_ReadInputDataBit(GA,P11) == 1)
		GPIO_ResetBits(GA,P11);
	else
		GPIO_SetBits(GA,P11);
	
	return 0;
}

/**
  * 函    数：EXTI15_10外部中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void EXTI15_10_IRQHandler(void)      /****每个中断引脚的函数都不太相同，此为10~15！要根据实际情况修改函数****/
{
	if (EXTI_GetITStatus(EXlin) == SET)		//判断是否是外部中断14号线触发的中断
	{
		//Delay_us(50);    //自己加的个用于精确
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(SW_GPIO(GPIOk),EXpin) == 0)
		{
			EXTI_Get();				//执行中断处理操作的函数
		}
		EXTI_ClearITPendingBit(EXlin);		//清除外部中断14号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}

