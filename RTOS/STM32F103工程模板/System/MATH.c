#include "stm32f10x.h"
/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  数字长度计算
  * @retval 返回数字的位数，可以用于表示文本数字使用
  */
uint32_t numlen(uint32_t num)//十进制计算数字的长度
{
    uint32_t len = 1;        // 初始长度为1
    for(; num > 9; ++len)    // 判断num是否大于9，否则长度+1
        num /= 10;	         // 使用除法进行运算，直到num小于1
    return len;              // 返回长度的值
}

