#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "stdio.h"

#define BYTE0(dwTemp) (*((char*)(&dwTemp)))
#define BYTE1(dwTemp) (*((char*)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char*)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char*)(&dwTemp) + 3))
	

void Serial_Init(void);
void Serial_SendByte(uint16_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
uint32_t Serial_Power(uint32_t X, uint32_t Y);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);
uint8_t Serial_GetRxFlag(void);
uint16_t Serial_GetRxData(void);

void Send_Senser(int16_t ACC_X, int16_t ACC_Y, int16_t ACC_Z, int16_t GYRO_X,
					int16_t GYRO_Y, int16_t GYRO_Z, int16_t MAG_X, int16_t MAG_Y, int16_t MAG_Z);

#endif
