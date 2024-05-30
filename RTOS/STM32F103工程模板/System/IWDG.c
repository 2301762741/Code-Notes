#include "stm32f10x.h"
#include "System.h"


/**T=0.025ms * Prescaler * ('Reload'+1)
  * 1.@brief  Sets IWDG Prescaler value.
  * @param1  IWDG_Prescaler: specifies the IWDG Prescaler value.
  *   This parameter can be one of the following values:
  *     @arg IWDG_Prescaler_4: IWDG prescaler set to 4
  *     @arg IWDG_Prescaler_8: IWDG prescaler set to 8
  *     @arg IWDG_Prescaler_16: IWDG prescaler set to 16
  *     @arg IWDG_Prescaler_32: IWDG prescaler set to 32
  *     @arg IWDG_Prescaler_64: IWDG prescaler set to 64
  *     @arg IWDG_Prescaler_128: IWDG prescaler set to 128
  *     @arg IWDG_Prescaler_256: IWDG prescaler set to 256
	*@retval None
	*
  * 2.@brief  Sets IWDG Reload value.
  * @param  Reload: specifies the IWDG Reload value.
  *   This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  */
void IWDGint(uint8_t IWDG_Prescaler_,uint16_t Reload)  
{
			/*IWDG初始化*/
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	//独立看门狗写使能
	IWDG_SetPrescaler(IWDG_Prescaler_);			//设置预分频，如为16
	IWDG_SetReload(Reload);							//设置重装值如，如Reload=2499独立看门狗的超时时间为1000ms。    T=0.025ms * Prescaler * ('Reload'+1)
	IWDG_ReloadCounter();							//重装计数器，喂狗
	IWDG_Enable();									//独立看门狗使能
}

//IWDG_ReloadCounter();							//重装计数器，喂狗



////////////////////////////////////WWDG窗口看门狗////////////////////////////////////////////////


/**
  * 1.@brief  Sets the WWDG Prescaler.
  * @param  WWDG_Prescaler: specifies the WWDG Prescaler.
  *   This parameter can be one of the following values:
  *     @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
  *     @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
  *     @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
  *     @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
  * @retval None
	*
  * 2.@brief  Sets the WWDG window value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  *   This parameter value must be lower than 0x80.
  * @retval None
	*
	* 3.@brief  Enables WWDG and load the counter value.                  
  * @param  Counter: specifies the watchdog counter value.
  *   This parameter must be a number between 0x40 and 0x7F.
  * @retval None
  */
void WWDGint(uint32_t WWDG_Prescaler_,uint8_t Reload,uint8_t Counter)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	//开启WWDG的时钟
	
	/*WWDG初始化*/
	WWDG_SetPrescaler(WWDG_Prescaler_);			//设置预分频为8   	
	WWDG_SetWindowValue(0x40 | Reload);					//设置最早喂狗时间，如设置Reload=(0x40 | 21)则窗口时间为30ms。    Tw=1/36M * 4096 * Prescaler * ('Reload'+1)
	WWDG_Enable(0x40 | Counter);							//使能并第一次喂狗并设置喂狗最晚时间,如Counter=(0x40 | 54)，则超时时间为50ms。  Te=1/36M * 4096 * Prescaler * (Tw-'Counter')
	//！0x40 是超时喂狗最高标志位，减溢出为零出发喂狗
}

//		WWDG_SetCounter(0x40 | 'Counter');					//重装计数器，喂狗放在程序最后，不然造成会开始就早喂狗的死循环

