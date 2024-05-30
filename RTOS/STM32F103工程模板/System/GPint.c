#include "stm32f10x.h"


/**
  * @brief  GPIO时钟与GPIO口的对应转换
  * @param  输入GPIO时钟，输出对应GPIO
	* @retval 目前只写了GPIOA，B，C的单组合
  */
GPIO_TypeDef* SW_GPIO(uint32_t RCC_APB2Periph)
{
	GPIO_TypeDef* GPIOk;
	//根据时钟的选择初始话对应GPIO块的选择
	switch(RCC_APB2Periph)
	{
		case RCC_APB2Periph_GPIOA: 
					GPIOk=GPIOA;
					break;
		case RCC_APB2Periph_GPIOB:
					GPIOk=GPIOB;
					break;
		case RCC_APB2Periph_GPIOC:
					GPIOk=GPIOC;
					break;
		/*case RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB:
					GPIOk=(GPIOA|GPIOB);
					break;
		case RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC:
					GPIOk=GPIOA;
					GPIOk=GPIOC;
					break;
		case RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC:
					GPIOk=GPIOB;
					GPIOk=GPIOC;
					break;
		case RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC:
					GPIOk=GPIOA;
					GPIOk=GPIOB;
					GPIOk=GPIOC;
					break;*/
	}
		return GPIOk;
}

/**
  * @brief  GPIO结构体初始换化函数
  * @param  第一个参数为选择GPIO块，可选GPA~GPD
						第二个参数为结构选择，填入传入结构体的名称
	* @retval 目前只写了GPIOA，B，C的组合
  */
void SW_GPIOi(uint32_t RCC_APB2Periph,GPIO_InitTypeDef* GPIO_InitStructure)
{
	//根据时钟的选择初始话对应GPIO块的选择
	switch(RCC_APB2Periph)
	{
		case RCC_APB2Periph_GPIOA: 
					GPIO_Init(GPIOA, GPIO_InitStructure);
					break;
		case RCC_APB2Periph_GPIOB:
					GPIO_Init(GPIOB, GPIO_InitStructure);
					break;
		case RCC_APB2Periph_GPIOC:
					GPIO_Init(GPIOC, GPIO_InitStructure);
					break;
		case RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB:
					GPIO_Init(GPIOA, GPIO_InitStructure);
					GPIO_Init(GPIOB, GPIO_InitStructure);
					break;
		case RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC:
					GPIO_Init(GPIOA, GPIO_InitStructure);
					GPIO_Init(GPIOC, GPIO_InitStructure);
					break;
		case RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC:
					GPIO_Init(GPIOB, GPIO_InitStructure);
					GPIO_Init(GPIOC, GPIO_InitStructure);
					break;
		case RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC:
					GPIO_Init(GPIOA, GPIO_InitStructure);
					GPIO_Init(GPIOB, GPIO_InitStructure);
					GPIO_Init(GPIOC, GPIO_InitStructure);
					break;
	}
}

/**
  * @brief  GPIO结构体初始换化函数
  * @param  第一个参数为选择GPIO块，可选GPA~GPD
	          第二个参数为端口模式的选择，OutPP推挽输出，OutDD开漏输出，IPD下拉输入，IPU上拉输入，AFPP
						第三个参数为对应引脚选择，P1~P18，注意有些端口是否有那些引脚
	* @retval 输出速度默认50MHZ
  */
void GPint(uint32_t RCC_APB2Periph, GPIOMode_TypeDef GPIO_mode, uint16_t GPIO_Pin/*, GPIOSpeed_TypeDef GPIO_Speed=GPIO_Speed_50MHz*/)
	{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	//开启内部时钟
														//使用各个外设前必须开启时钟，否则对外设的操作无效
	
/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_mode;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				//GPIO引脚，赋值为第13号引脚
		//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_ALL ;       //GPIO_Pin_ALL 选择全部GPIOk上的全部引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz /*GPIO_Speed*/;		//GPIO速度，默认赋值为50MHz

	SW_GPIOi(RCC_APB2Periph,&GPIO_InitStructure);
	//GPIO_Init(GPIO_k, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
															//函数内部会自动根据结构体的参数配置相应寄存器
															//实现GPIOC的初始化
	/*设置GPIO引脚的高低电平*/
		/*若不设置GPIO引脚的电平，则在GPIO初始化为推挽输出后，指定引脚默认输出低电平，未指定则默认上电高电平*/	
}

