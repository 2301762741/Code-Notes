#include "stm32f4xx.h"                  // Device header
#include "Delay.h"

void IIC_W_SCL(uint8_t value)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)value);
	Delay_us(1);
}

void IIC_W_SDA(uint8_t value)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)value);
	Delay_us(1);
}

uint8_t IIC_R_SDA()
{
	uint8_t value;
	value = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3);
	Delay_us(1);
	return value;
}

void IIC_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_2|GPIO_Pin_3);
}

void IIC_Start()
{
	IIC_W_SDA(1);
	IIC_W_SCL(1);
	IIC_W_SDA(0);
	IIC_W_SCL(0);
}

void IIC_Stop()
{
	IIC_W_SDA(0);
	IIC_W_SCL(1);
	IIC_W_SDA(1);
}

void IIC_SendByte(uint8_t Byte)
{
	int i;
	for(i = 0; i<8; i++)
	{
		IIC_W_SDA(Byte&(0x80>>i));
		IIC_W_SCL(1);
		IIC_W_SCL(0);
	}
}

uint8_t IIC_ReceiveByte()
{
	int i;
	uint8_t Byte = 0x00;
	IIC_W_SDA(1);
	
	for(i = 0; i<8; i++)
	{
		IIC_W_SCL(1);
		if(IIC_R_SDA() == 1)
		{
			Byte = Byte|(0x80>>i);
		}
		IIC_W_SCL(0);
	}
	return Byte;
}

void IIC_SendACK(uint8_t Byte)
{
	IIC_W_SDA(Byte);
	IIC_W_SCL(1);
	IIC_W_SCL(0);
}

uint8_t IIC_ReceiveACK()
{
	uint8_t Byte;
	IIC_W_SDA(1);
	
	IIC_W_SCL(1);
	Byte = IIC_R_SDA();
	IIC_W_SCL(0);
	
	return Byte;
}

