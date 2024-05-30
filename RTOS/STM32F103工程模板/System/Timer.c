#include "stm32f10x.h"                  // Device header
#include "System.h"

#define TIMk RCC_APB1Periph_TIM2
#define NVIC_IRQ TIM2_IRQn     //NVIC触发通道选择
//此外还需要修改对应定时器的触发函数名
//#define RCC_GPIO RCC_APB2Periph_GPIOA   //应用交复用时使用

/**
  * 函    数：返回定时器CNT的值
  * 参    数：无
  * 返 回 值：定时器CNT的值，范围：0~65535
  */
uint16_t Tim_Count(void)
{
	return TIM_GetCounter(TIM2);	//返回定时器TIM2的CNT
}

/**
  * 函    数：选择定时器函数（待写）
  * 参    数：传入对应定时器时钟就能选择对应定时
  * 返 回 值：TIM1~3
	* 使用方法：TIM_TypeDef* TIM_k=SW_TIM(TIMk);  //TIMk传入的TIM时钟值
  */
TIM_TypeDef* SW_TIM(uint32_t RCC_APB1Periph)
{
	TIM_TypeDef* TIM_k;        //这里同时调用全局时会导致地址冲突
	switch(TIMk)
	{
		case RCC_APB2Periph_TIM1: 
					TIM_k=TIM1;break;
		case RCC_APB1Periph_TIM2:
					TIM_k=TIM2;break;
		case RCC_APB1Periph_TIM3:
					TIM_k=TIM3;break;
	}
	return TIM_k;
}
/**
  * 函    数：定时中断初始化
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数配置为外部时钟，定时器相当于计数器
  */
void TIMint(void)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(TIMk, ENABLE);			//开启TIM2的时钟
	
	
	/*******使用外部时钟的代码，注释默认使用RCC内部始终******/
	/*PA0口的GPIO初始化
	RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);			//开启GPIOA的时钟

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;         //固定外接时钟引脚PA0，无法选择
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	SW_GPIOi(GPIOk, &GPIO_InitStructure);						//将PA0引脚初始化为上拉输入
	
	//外部时钟配置
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);
																//选择外部时钟模式2，时钟从TIM_ETR引脚输入
																//注意TIM2的ETR引脚固定为PA0，无法随意更改
																//最后一个滤波器参数加到最大0x0F，可滤除时钟信号抖动*/
	/*选择定时器*/
	TIM_TypeDef* TIM_k=SW_TIM(TIMk);
	
		/*配置时钟源*/
	TIM_InternalClockConfig(TIM_k);		//选择TIM_k为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;					//计数周期，即重装器值，达到最大值触发更新事件并重置 CNT最大值，因为从0开始计数，所以计数10000次是10000-1,每秒有10000计次/10000次触发 即每1秒触发一次
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;				//设置时钟预分频，7200-1就是每 时钟频率每秒(72Mhz)/7200=10000 个时钟周期计数器加1,每100微秒计数器+1
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			//重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM_k, &TIM_TimeBaseInitStructure);				//将结构体变量交给TIM_TimeBaseInit，配置TIM2的时基单元	

	                         /*****中断输出配置*****/
	TIM_ClearFlag(TIM_k, TIM_FLAG_Update);						//清除定时器更新标志位
																//TIM_TimeBaseInit函数末尾，手动产生了更新事件
																//若不清除此标志位，则开启中断后，会立刻进入一次中断
																//如果不介意此问题，则不清除此标志位也可
																
	TIM_ITConfig(TIM_k, TIM_IT_Update, ENABLE);					//开启TIMk的更新中断
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置NVIC为分组2
																//即抢占优先级范围：0~3，响应优先级范围：0~3
																//此分组配置在整个工程中仅需调用一次
																//若有多个中断，可以把此代码放在main函数内，while循环之前
																//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQ;				//选择配置NVIC的TIM2线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//指定NVIC线路的抢占优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
	
	
	/*TIM使能*/
	TIM_Cmd(TIM_k, ENABLE);			//使能TIM2，定时器开始运行
}


/* 定时器中断函数，可以复制到使用它的地方
void TIM2_IRQHandler(void)   //注意使用时要修改应定时器的中断函数与对应定时器
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		// 实现功能部分
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
	}
}
*/
