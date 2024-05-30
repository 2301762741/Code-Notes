#include "stm32f10x.h"                  // Device header
#include "System.h"

#define TIMk RCC_APB1Periph_TIM2          //开启TIM2时钟
#define RCC_GPIO RCC_APB2Periph_GPIOA
#define GPpin P0/*|P1|P2*/                //GPIO_Pin_15;   //PA0的重映射端口，注意不同引脚对应了不同通道，其重映射位置也是不同的
//改端口要改下面对应的通道 ，不是PWM输出端口是外设固定端口，PA0对应通道1以此向下类推

TIM_TypeDef* TIM_k;/*选择定时器*/

/**
  * 函    数：PWM初始化
  * 参    数：无
  * 返 回 值：无
  */
void PWMint(void)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(TIMk, ENABLE);			//开启TIM_k的时钟
	RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);			//开启GPIOA的时钟
	
	/*GPIO重映射*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//开启AFIO的时钟，重映射必须先开启AFIO的时钟
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM_k, ENABLE);			//将TIM_k的引脚部分重映射，具体的映射方案需查看参考手册
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);		//将JTAG调试功能解除，作为普通GPIO引脚使用	
				/***调试引脚有PB3，PB4，PA13，PA14，PA15***/
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPpin ;		//GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	SW_GPIOi(RCC_GPIO, &GPIO_InitStructure);							//将PA0引脚初始化为复用推挽输出	
																	//受外设控制的引脚，均需要配置为复用模式		
	
			/*选择定时器*/
	TIM_k=SW_TIM(TIMk);
	
	/*配置时钟源*/
	TIM_InternalClockConfig(TIM_k);		//选择TIM_k为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;					//计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;				//预分频器，72MHZ/720即PSC的值,1000HZ脉冲
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM_k, &TIM_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM_k的时基单元
	
	                           /*****输出比较初始化*****/
	TIM_OCInitTypeDef TIM_OCInitStructure;							//定义结构体变量
	TIM_OCStructInit(&TIM_OCInitStructure);							//结构体初始化，若结构体没有完整赋值
																	//则最好执行此函数，给结构体所有成员都赋一个默认值
																	//避免结构体初值不确定的问题
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				//输出比较模式，选择PWM模式1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		//输出极性，选择为高，若选择极性为低，则输出高低电平取反
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;								//初始的CCR值
	TIM_OC1Init(TIM_k, &TIM_OCInitStructure);					//将结构体变量交给TIM_OC1Init，配置TIM_k的输出比较通道1          /********此处需要该对应的通道函数**********/
	//TIM_OC2Init(TIM_k, &TIM_OCInitStructure);					//共用一个计数器脉冲的通道，可分开设置占空比	
	//TIM_OC3Init(TIM_k, &TIM_OCInitStructure);					//MY_三路开三通道写法
	
	/*TIM使能*/
	TIM_Cmd(TIM_k, ENABLE);			//使能TIM_k，定时器开始运行
	
	PWM_SetCCR(100);   //上电灭灯                                                                                                                          
}


/**
	* 函    数：PWM设置PSC来改变频率，固定ARR为100时
  * 参    数：HZ 要写入的ARR的值，范围：72Mhz/PSC
  * 返 回 值：无
  * 注意事项：PSC与ARR共同决定频率，公式 HZ=72Mhz/(PSC-1)/(ARR-1)
  */
void PWM_SetPSC(uint16_t Prescaler)
{
	TIM_PrescalerConfig(TIM_k, Prescaler, TIM_PSCReloadMode_Immediate);		//设置PSC的值,此模式为立即改变模式
}

/**
  * 函    数：PWM设置CCR来改变占空比
  * 参    数：Compare 要写入的CCR的值，范围：0~100
  * 返 回 值：无
  * 注意事项：CCR和ARR共同决定占空比，此函数仅设置CCR的值，并不直接是占空比
  *           占空比Duty = CCR / (ARR + 1)
  */
void PWM_SetCCR(uint16_t Compare)
{
	TIM_SetCompare1(TIM_k, Compare);		//设置通道1的CCR的值                           /******此处也需要该对应的设置函数********/
	//TIM_SetCompare2(TIM_k, Compare+16);		//设置通道2的CCR1的值，对应PA1口
	//TIM_SetCompare3(TIM_k, Compare+32);		//设置通道3的CCR1的值
}

/**
  * 函    数：呼吸灯循环
  * 参    数：无
  * 返 回 值：无
  * 注意事项：分辨率为100，CCR为0~100
	*         	占空比Duty = CCR / (ARR + 1)
  */
void huxiLED(void)
{
		for (int i = 100; i > 0; i--)
		{
			PWM_SetCCR(i);	    //依次将定时器的CCR寄存器设置为100~0，PWM占空比逐渐减小，LED逐渐变亮
			Delay_ms(20);				//延时20ms
		}
		for (int i = 0; i <= 100; i++)
		{
			PWM_SetCCR(i);			//依次将定时器的CCR寄存器设置为0~100，PWM占空比逐渐增大，LED逐渐变暗
			Delay_ms(20);				//延时20ms
		}
}
