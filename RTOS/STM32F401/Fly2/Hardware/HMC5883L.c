#include "stm32f4xx.h"                  // Device header
#include "IIC.h"
#include "HMC5883L_Reg.h"
#include "HMC5883L.h"


extern HMC5883L_DataTypeDef Mag;

void HMC5883L_WriteReg(uint8_t reg, uint8_t data)
{
	IIC_Start();
	IIC_SendByte((HMC5883L_Address)<<1|0);
	IIC_ReceiveACK();
	IIC_SendByte(reg);
	IIC_ReceiveACK();
	
	IIC_SendByte(data);
	IIC_ReceiveACK();
	IIC_Stop();
}

uint8_t HMC5883L_ReadReg(uint8_t reg)
{
	uint8_t data;
	IIC_Start();
	IIC_SendByte((HMC5883L_Address)<<1|0);
	IIC_ReceiveACK();
	IIC_SendByte(reg);
	IIC_ReceiveACK();
	
	IIC_Start();
	IIC_SendByte((HMC5883L_Address)<<1|1);
	IIC_ReceiveACK();
	data = IIC_ReceiveByte();
	IIC_SendACK(0);
	IIC_Stop();
	
	return data;
}

void HMC5883L_Init(void)
{
//	IIC_Init();
	
	HMC5883L_WriteReg(HMC5883L_Config_A,0x70);
	HMC5883L_WriteReg(HMC5883L_Config_B,0x20);
	HMC5883L_WriteReg(HMC5883L_Mode,0x00);
	
}


void HMC5883L_GetData(void)
{
	
	uint8_t DataH,DataL;
	
	DataH = HMC5883L_ReadReg(HMC5883L_MAGNETIC_XOUT_H);
	DataL = HMC5883L_ReadReg(HMC5883L_MAGNETIC_XOUT_L);
	Mag.MagX = (int16_t)(DataH<<8)|DataL;
	
	DataH = HMC5883L_ReadReg(HMC5883L_MAGNETIC_YOUT_H);
	DataL = HMC5883L_ReadReg(HMC5883L_MAGNETIC_YOUT_L);
	Mag.MagY = (int16_t)(DataH<<8)|DataL;
	
	DataH = HMC5883L_ReadReg(HMC5883L_MAGNETIC_ZOUT_H);
	DataL = HMC5883L_ReadReg(HMC5883L_MAGNETIC_ZOUT_L);
	Mag.MagZ = (int16_t)(DataH<<8)|DataL;

}
