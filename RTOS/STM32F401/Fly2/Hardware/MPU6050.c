#include "stm32f4xx.h"                  // Device header
#include "IIC.h"
#include "MPU6050_Reg.h"
#include "Serial.h"
#include "MPU6050.h"


extern MPU6050_DataTypeDef Acc_Gyro;
extern Float_t fGyro;


void MPU6050_WriteReg(uint8_t reg, uint8_t data)
{
	IIC_Start();
	IIC_SendByte((MPU6050_Address)<<1|0);
	IIC_ReceiveACK();
	IIC_SendByte(reg);
	IIC_ReceiveACK();
	
	IIC_SendByte(data);
	IIC_ReceiveACK();
	IIC_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t reg)
{
	uint8_t data;
	IIC_Start();
	IIC_SendByte((MPU6050_Address)<<1|0);
	IIC_ReceiveACK();
	IIC_SendByte(reg);
	IIC_ReceiveACK();
	
	IIC_Start();
	IIC_SendByte((MPU6050_Address)<<1|1);
	IIC_ReceiveACK();
	data = IIC_ReceiveByte();
	IIC_SendACK(0);
	IIC_Stop();
	
	return data;
}

void MPU6050_Init(void)
{
//	IIC_Init();
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x00);		//解除休眠状态,使用内部8MHz振荡器
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x00);		//采样分频 (采样频率 = 陀螺仪输出频率 / (1+DIV)，采样频率1000hz）
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);			//设置低通滤波
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);		//陀螺仪满量程+-2000度/秒 (最低分辨率 = 2^15/2000 = 16.4LSB/度/秒
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x08);	//加速度满量程+-4g   (最低分辨率 = 2^15/4g = 8192LSB/g )
	
//	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);
//	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
//	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
//	MPU6050_WriteReg(MPU6050_CONFIG,0x06);
//	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
//	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);
	
	MPU6050_WriteReg(MPU6050_INT_PIN_CFG, 0x02);		//开启BYPASS模式（辅助IIC），使HMC5883L的总线直接与STM32的总线接口物理连接
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}



void MPU6050_GetData(void)
{
	//uint还是int
	int8_t DataH,DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	Acc_Gyro.AccX = (int16_t)(DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	Acc_Gyro.AccY = (int16_t)(DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	Acc_Gyro.AccZ = (int16_t)(DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	Acc_Gyro.GyroX = (int16_t)(DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	Acc_Gyro.GyroY = (int16_t)(DataH<<8)|DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	Acc_Gyro.GyroZ = (int16_t)(DataH<<8)|DataL;
	
	fGyro.x = (float)(Acc_Gyro.GyroX*RAW_TO_RAD);
	fGyro.y = (float)(Acc_Gyro.GyroY*RAW_TO_RAD);
	fGyro.z = (float)(Acc_Gyro.GyroZ*RAW_TO_RAD);
}

//以下为发送加速度计数据给匿名解析，问题是数据过长无法解析
//下一步发送欧拉角数据
void Send_BUFF(void)
{
	//MPU6050_GetData(&Data1);
	
	uint8_t i;
	uint8_t sumcheck = 0;
	uint8_t addcheck = 0;
	uint8_t _cnt=0;							
	int8_t BUFF[30];
	
	BUFF[_cnt++] = 0xAA;
	BUFF[_cnt++] = 0xFF;
	BUFF[_cnt++] = 0x01;
	BUFF[_cnt++] = 13;
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	BUFF[_cnt++] = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
//	BUFF[_cnt++] = BYTE0(Data1.AccX);
//	BUFF[_cnt++] = BYTE1(Data1.AccX);
//	BUFF[_cnt++] = BYTE0(Data1.AccY);
//	BUFF[_cnt++] = BYTE1(Data1.AccY);
//	BUFF[_cnt++] = BYTE0(Data1.AccZ);
//	BUFF[_cnt++] = BYTE1(Data1.AccZ);
//	BUFF[_cnt++] = BYTE0(Data1.GyroX);
//	BUFF[_cnt++] = BYTE1(Data1.GyroX);
//	BUFF[_cnt++] = BYTE0(Data1.GyroY);
//	BUFF[_cnt++] = BYTE1(Data1.GyroY);
//	BUFF[_cnt++] = BYTE0(Data1.GyroZ);
//	BUFF[_cnt++] = BYTE1(Data1.GyroZ);
	BUFF[_cnt++] = 0;
	
	for(i=0;i<BUFF[3]+4;i++) 
	{
		sumcheck+=BUFF[i];
		addcheck+=sumcheck;
	}
	BUFF[_cnt++]=sumcheck;	
	BUFF[_cnt++]=addcheck;
	
	for(i=0;i<_cnt;i++)
	{
		Serial_SendByte(BUFF[i]);
	}
}	

//void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
//						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
//{
//	uint8_t DataH, DataL;
//	
//	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
//	*AccX = (DataH << 8) | DataL;
//	
//	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
//	*AccY = (DataH << 8) | DataL;
//	
//	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
//	*AccZ = (DataH << 8) | DataL;
//	
//	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
//	*GyroX = (DataH << 8) | DataL;
//	
//	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
//	*GyroY = (DataH << 8) | DataL;
//	
//	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
//	*GyroZ = (DataH << 8) | DataL;
//}

