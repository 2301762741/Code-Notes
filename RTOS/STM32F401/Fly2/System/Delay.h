#include "stm32f4xx.h"                  // Device header
#include "ucos_ii.h"
#include "core_cm4.h"
#include "os_cpu.h"

void Delay_Init(u8 SYSCLK);
void Delay_us(u32 nus);
void Delay_ms(u16 nms);
