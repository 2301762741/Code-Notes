#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"

/*****__DELAY_H*****/
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);
void TimingDelay_Decrement (void);

/*****__LED_H*****/
void GPIO_LED2int(void);
void LED_ON(void);
void LED_OFF(void);


#endif
