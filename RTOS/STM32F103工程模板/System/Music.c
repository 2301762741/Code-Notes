#include "stm32f10x.h"                
#include "System.h"
#include "Music_base.h"

//蜂鸣器端口定义
#define GPIO GA
#define PIN P3
#define TIMk RCC_APB1Periph_TIM2
#define NVIC_IRQ TIM2_IRQn     //NVIC触发通道选择

void Music()
{
	//Music_FMQ(SPEED/4*code_Music[MusicSelect],MusicTable[FreqSelect]);
	//Delay_s(1);
	
	while(1)
	{
		if(code_Music[MusicSelect]!=0xFF)	//如果不是停止标志位
		{
			FreqSelect=code_Music[MusicSelect++];	//选择音符对应的频率
			Music_FMQ(SPEED/4*code_Music[MusicSelect++],MusicTable[FreqSelect]);
			Delay_ms(5);	//音符间短暂停顿
		}
		else	//如果是停止标志位
		{
			//TIM_Cmd(TIM2, DISABLE);			//使能TIM2，定时器开始运行
			//while(1);
		}
	}
}

/**
  * 函    数：无缘蜂鸣器单音部分
  * 参    数：翻转次数（总时间=翻转次数*翻转时间/2），震动频率（HZ）
  * 返 回 值：无
  */
void Music_FMQ_turn()
{
	//初始化端口
	GPint(GPA,OutPP,PIN);
	
	if(GPIO_ReadInputDataBit(GA,P3)== SET)
		GPIO_ResetBits(GPIO,PIN);
	else
		GPIO_SetBits(GPIO,PIN);
}

/**
  * 函    数：无缘蜂鸣器单音部分
  * 参    数：鸣响的时间（ms），震动频率（HZ）
  * 返 回 值：无
  */
void Music_FMQ(double times,uint16_t hz)
{
	double time=1.0/hz*1000000;       //鸣响周期
	for(int i=0;i<1000.0/time*times;i++)   //鸣响1毫秒震动的次数*毫秒数
	{
		Music_FMQ_turn();
		Delay_us(time/2);       //需翻转两次响一次
	}
	//Delay_s(2);  //间隔时间
}

/**
	* 函    数：递升播放不同频率音
  * 参    数：无
  * 返 回 值：无.
  */
void Music_FMQ_xun()
{
		for(int i=10;i<30000;i+=10)
    {
			OLED_Clear_Part(2,4,16); OLED_ShowString(2,1,"HZ:"); OLED_ShowNum(2,4,i,numlen(i));
			Music_FMQ(200,i);    //递升频率播放
			Delay_ms(700);
    }
}

//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//	{
//		if(FreqTable[FreqSelect])	//如果不是休止符
//		{
//			TIM_PrescalerConfig(TIM2,FreqTable[FreqSelect], TIM_PSCReloadMode_Immediate);		//设置PSC的值,此模式为立即改变模式
//			Music_FMQ_turn();
//		}
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}

void Music_TIM()
{
		/*开启时钟*/
	RCC_APB1PeriphClockCmd(TIMk, ENABLE);			//开启TIM2的时钟
	
	/*选择定时器*/
	TIM_TypeDef* TIM_k=SW_TIM(TIMk);
	
		/*配置时钟源*/
	TIM_InternalClockConfig(TIM_k);		//选择TIM_k为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;					//计数周期，即重装器值，达到最大值触发更新事件并重置 CNT最大值，因为从0开始计数，所以计数10000次是10000-1,每秒有10000计次/10000次触发 即每1秒触发一次
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;				//设置时钟预分频，7200-1就是每 时钟频率每秒(72Mhz)/7=10000 多个时钟周期计数器加1,约1微秒计数器+1
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
	
//	while(1)
//	{
//		if(code_Music[MusicSelect]!=0xFF)	//如果不是停止标志位
//		{
//			FreqSelect=code_Music[MusicSelect];	//选择音符对应的频率
//			MusicSelect++;
//			Delay_ms(SPEED/4*code_Music[MusicSelect]);	//选择音符对应的时值
//			MusicSelect++;
//			TIM_Cmd(TIM2, DISABLE);			//使能TIM2，定时器开始运行
//			Delay_ms(5);	//音符间短暂停顿
//			TIM_Cmd(TIM2, ENABLE);			//使能TIM2，定时器开始运行
//		}
//		else	//如果是停止标志位
//		{
//			TIM_Cmd(TIM2, DISABLE);			//使能TIM2，定时器开始运行
//			while(1);
//		}
//	}
}

//void MusicTm()
//{
//	while(1)
//	{
//		if(code_Music[MusicSelect]!=0xFF)	//如果不是停止标志位
//		{
//			FreqSelect=code_Music[MusicSelect];	//选择音符对应的频率
//			MusicSelect++;
//			Delay_ms(SPEED/4*code_Music[MusicSelect]);	//选择音符对应的时值
//			MusicSelect++;

//			TIM_Cmd(TIM2, DISABLE);			//失能TIM2，定时器不运行
//			Delay_ms(5);	//音符间短暂停顿
//			TIM_Cmd(TIM2, ENABLE);			//使能TIM2，定时器开始运行
//		}
//		else	//如果是停止标志位
//		{
//			TIM_Cmd(TIM2, DISABLE);			//失能TIM2，定时器运行
//			break;
//		}
//	}
//}

//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//	{
//		TIM_SetCounter(TIM2,FreqTable[FreqSelect]);
//		Music_FMQ_turn();
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}

//void Timer0_Routine() interrupt 1
//{
//	if(FreqTable[FreqSelect])	//如果不是休止符
//	{
//		/*取对应频率值的重装载值到定时器*/
//		TL0 = FreqTable[FreqSelect]%256;		//设置定时初值
//		TH0 = FreqTable[FreqSelect]/256;		//设置定时初值
//		Buzzer=!Buzzer;	//翻转蜂鸣器IO口
//	}
//}
