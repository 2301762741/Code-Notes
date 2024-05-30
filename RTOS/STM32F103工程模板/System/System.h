#ifndef __DELAY_H
#define __DELAY_H

#define GPA RCC_APB2Periph_GPIOA 
#define GPB RCC_APB2Periph_GPIOB 
#define GPC RCC_APB2Periph_GPIOC 
//#define GPD RCC_APB2Periph_GPIOD 
#define GA GPIOA
#define GB GPIOB
#define GC GPIOC
//#define GD GPIOD
#define OutPP GPIO_Mode_Out_PP
#define OutOD  GPIO_Mode_Out_OD 
#define AIN  GPIO_Mode_AIN 
#define InFLOATING  GPIO_Mode_IN_FLOATING 
#define IPD GPIO_Mode_IPD 
#define IPU GPIO_Mode_IPU 
#define AfOD GPIO_Mode_AF_OD 
#define AfPP  GPIO_Mode_AF_PP 
//#define Bit_RESET 0
//#define Bit_SET 1
#define P15 GPIO_Pin_15 
#define P14 GPIO_Pin_14 
#define P13 GPIO_Pin_13 
#define P12 GPIO_Pin_12 
#define P11 GPIO_Pin_11 
#define P10 GPIO_Pin_10 
#define P9 GPIO_Pin_9 
#define P8 GPIO_Pin_8 
#define P7 GPIO_Pin_7 
#define P6 GPIO_Pin_6 
#define P5 GPIO_Pin_5 
#define P4 GPIO_Pin_4 
#define P3 GPIO_Pin_3 
#define P2 GPIO_Pin_2 
#define P1 GPIO_Pin_1 
#define P0 GPIO_Pin_0 

/*********GPIO**********/
void GPint(uint32_t RCC_APB2Periph, GPIOMode_TypeDef GPIO_mode, uint16_t GPIO_Pin);  //同时开启多个时钟还有问题
void SW_GPIOi(uint32_t RCC_APB2Periph,GPIO_InitTypeDef* GPIO_InitStructure);
GPIO_TypeDef* SW_GPIO(uint32_t RCC_APB2Periph);//（待完善）

/*********EXTI**********/
void EXTIint(void);
uint16_t EXTI_Get(void);

/*********Timer**********/
void TIMint(void);
TIM_TypeDef* SW_TIM(uint32_t RCC_APB1Periph);//（待测）
uint16_t Tim_Count(void);

/*********PWN**********/
void PWMint(void);
void PWM_SetCCR(uint16_t Compare);
void PWM_SetPSC(uint16_t Prescaler);
void huxiLED(void);

/*********PWN_IC(没怎么优化过，安全)**********/
void ICint(void);
uint32_t IC_GetHZ(void);
uint32_t IC_GetCCR(void);

/*********DMA**********/
void MyDMAint(uint32_t AddrA, uint32_t AddrB, uint16_t Size);
void MyDMA_Transfer(void);
//测试代码

/*********AD +DMA**********/
extern uint16_t AD_Value[4];
void ADint(void);

/*********USE**********/
extern uint8_t USE_RxData;
uint8_t USE_GetRxFlag(void);
void USEint(void);
void USE_SendByte(uint8_t Byte);
void USE_SendArray(uint8_t *Array, uint16_t Length);
void USE_SendString(char *String);
void USE_SendPacket(uint8_t *USE_TxPacket,uint8_t n);
void USE_SendNumber(uint32_t Number, uint8_t Length);
void USE_Printf(char *format, ...);

/*********HC-Ly（蓝牙模块，未完善）**********/
extern uint8_t HC_RxSTA;
//extern char ZxData[100];   //数据缓存
void HCint(void);
void HC_SendString(char *Buf);
void HC_GetData(char *Buf);
uint8_t HC_Orde(char *Buf);

/*********MyI2C总线**********/
void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);
//void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);
//void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
//uint8_t MPU6050_ReadReg(uint8_t RegAddress);
//uint8_t MPU6050_GetID(void);

/*********MyISPI总线**********/
void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

/*********W25Q存储模块**********/
void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count);
void W25Q64_SectorErase(uint32_t Address);
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);
void W25Q64_Show(void);

/*********FLASH存储模块**********/
uint32_t MyFLASH_ReadWord(uint32_t Address);
uint16_t MyFLASH_ReadHalfWord(uint32_t Address);
uint8_t MyFLASH_ReadByte(uint32_t Address);
void MyFLASH_EraseAllPages(void);
void MyFLASH_ErasePage(uint32_t PageAddress);
void MyFLASH_ProgramWord(uint32_t Address, uint32_t Data);
void MyFLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

extern uint16_t Store_Data[];
void Store_Init(void);
void Store_Save(void);
void Store_Clear(void);

/*********MyRTC时钟与备份模块**********/
extern uint16_t MyRTC_Time[];
void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);
void MyRTC_ShowTime(void);

/*********WDG独立看门狗**********/
void IWDGint(uint8_t IWDG_Prescaler_,uint16_t Reload);     //T=0.025ms * Prescaler * ('Reload'+1)
//IWDG_ReloadCounter();							//重装计数器，喂狗
void WWDGint(uint32_t WWDG_Prescaler_,uint8_t Reload,uint8_t Counter);  //Tw=1/36M * 4096 * Prescaler * ('Reload'+1)；Te=1/36M * 4096 * Prescaler * (Tw-'Counter')
//WWDG_SetCounter(0x40 | 'Counter');					//重装计数器，喂狗放在程序最后，不然造成会开始就早喂狗的死循环 Counter最早喂狗时间的参数

/*********Music**********/
void Music_FMQ_turn(void);
void Music_FMQ(double times,uint16_t hz);
void Music_FMQ_xun(void);
void Music(void);
void Music_TIM(void);
void MusicTm(void);

/*********Math**********/
uint32_t numlen(uint32_t num);
uint32_t Pow(uint32_t X, uint32_t Y);

/*********Delay**********/
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

/*********oled**********/
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Clear_Part(uint8_t Line, uint8_t start, uint8_t end);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif
