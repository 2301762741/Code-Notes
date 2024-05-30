#include "stm32f10x.h"                  // Device header
#include "System.h"

/*引脚配置层*/
#define GPIOk GPIOB   //引脚初始化，注意：还需改对应GPIO时钟
#define SCL GPIO_Pin_10     //时钟引脚
#define SDA GPIO_Pin_11			//数据引脚

/**
  * 函    数：I2C写SCL引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入SCL的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SCL为低电平，当BitValue为1时，需要置SCL为高电平
  */
void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOk, SCL, (BitAction)BitValue);		//根据BitValue，设置SCL引脚的电平
	Delay_us(10);												//延时10us，防止时序频率超过要求
}

/**
  * 函    数：I2C写SDA引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入SDA的电平，范围0~0xFF
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SDA为低电平，当BitValue非0时，需要置SDA为高电平
  */
void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOk, SDA, (BitAction)BitValue);		//根据BitValue，设置SDA引脚的电平，BitValue要实现非0即1的特性
	Delay_us(10);												//延时10us，防止时序频率超过要求
}

/**
  * 函    数：I2C读SDA引脚电平
  * 参    数：无
  * 返 回 值：协议层需要得到的当前SDA的电平，范围0~1
  * 注意事项：此函数需要用户实现内容，当前SDA为低电平时，返回0，当前SDA为高电平时，返回1
  */
uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOk, SDA);		//读取SDA电平
	Delay_us(10);												//延时10us，防止时序频率超过要求
	return BitValue;											//返回SDA电平
}

/**
  * 函    数：I2C初始化
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，实现SCL和SDA引脚的初始化
  */
void MyI2C_Init(void)
{
 						/**********软件I2C初始化**********/	
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOk的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = SCL | SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOk, &GPIO_InitStructure);					//将PB10和PB11引脚初始化为开漏输出
	
	/*设置默认电平*/
	GPIO_SetBits(GPIOk, SCL | SDA);			//设置PB10和PB11引脚初始化后默认为高电平（释放总线状态）
	
	
							/**********硬件I2C初始化**********/	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);		//开启I2C2的时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
//	
//	/*GPIO初始化*/
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;   //引脚固定
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);					//将PB10和PB11引脚初始化为复用开漏输出
//	
//	/*I2C初始化*/
//	I2C_InitTypeDef I2C_InitStructure;						//定义结构体变量
//	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;				//模式，选择为I2C模式
//	I2C_InitStructure.I2C_ClockSpeed = 50000;				//时钟速度，选择为50KHz
//	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		//时钟占空比，选择Tlow/Thigh = 2
//	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;				//应答，选择使能
//	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	//应答地址，选择7位，从机模式下才有效
//	I2C_InitStructure.I2C_OwnAddress1 = 0x00;				//自身地址，从机模式下才有效
//	I2C_Init(I2C2, &I2C_InitStructure);						//将结构体变量交给I2C_Init，配置I2C2
//	
//	/*I2C使能*/
//	I2C_Cmd(I2C2, ENABLE);									//使能I2C2，开始运行
}

/*协议层*/

/**
  * 函    数：I2C起始
  * 参    数：无
  * 返 回 值：无
  */
void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);							//释放SDA，确保SDA为高电平
	MyI2C_W_SCL(1);							//释放SCL，确保SCL为高电平
	MyI2C_W_SDA(0);							//在SCL高电平期间，拉低SDA，产生起始信号
	MyI2C_W_SCL(0);							//起始后把SCL也拉低，即为了占用总线，也为了方便总线时序的拼接
}

/**
  * 函    数：I2C终止
  * 参    数：无
  * 返 回 值：无
  */
void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);							//拉低SDA，确保SDA为低电平
	MyI2C_W_SCL(1);							//释放SCL，使SCL呈现高电平
	MyI2C_W_SDA(1);							//在SCL高电平期间，释放SDA，产生终止信号
}

/**
  * 函    数：I2C发送一个字节
  * 参    数：Byte 要发送的一个字节数据，范围：0x00~0xFF
  * 返 回 值：无
  */
void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i ++)				//循环8次，主机依次发送数据的每一位
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));	//使用掩码的方式取出Byte的指定一位数据并写入到SDA线
		MyI2C_W_SCL(1);						//释放SCL，从机在SCL高电平期间读取SDA
		MyI2C_W_SCL(0);						//拉低SCL，主机开始发送下一位数据
	}
}

/**
  * 函    数：I2C接收一个字节
  * 参    数：无
  * 返 回 值：接收到的一个字节数据，范围：0x00~0xFF
  */
uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;					//定义接收的数据，并赋初值0x00，此处必须赋初值0x00，后面会用到
	MyI2C_W_SDA(1);							//接收前，主机先确保释放SDA，避免干扰从机的数据发送
	for (i = 0; i < 8; i ++)				//循环8次，主机依次接收数据的每一位
	{
		MyI2C_W_SCL(1);						//释放SCL，主机机在SCL高电平期间读取SDA
		if (MyI2C_R_SDA() == 1){Byte |= (0x80 >> i);}	//读取SDA数据，并存储到Byte变量
														//当SDA为1时，置变量指定位为1，当SDA为0时，不做处理，指定位为默认的初值0
		MyI2C_W_SCL(0);						//拉低SCL，从机在SCL低电平期间写入SDA
	}
	return Byte;							//返回接收到的一个字节数据
}

/**
  * 函    数：I2C发送应答位
  * 参    数：Byte 要发送的应答位，范围：0~1，0表示应答，1表示非应答
  * 返 回 值：无
  */
void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);					//主机把应答位数据放到SDA线
	MyI2C_W_SCL(1);							//释放SCL，从机在SCL高电平期间，读取应答位
	MyI2C_W_SCL(0);							//拉低SCL，开始下一个时序模块
}

/**
  * 函    数：I2C接收应答位
  * 参    数：无
  * 返 回 值：接收到的应答位，范围：0~1，0表示应答，1表示非应答
  */
uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;							//定义应答位变量
	MyI2C_W_SDA(1);							//接收前，主机先确保释放SDA，避免干扰从机的数据发送
	MyI2C_W_SCL(1);							//释放SCL，主机机在SCL高电平期间读取SDA
	AckBit = MyI2C_R_SDA();					//将应答位存储到变量里
	MyI2C_W_SCL(0);							//拉低SCL，开始下一个时序模块
	return AckBit;							//返回定义应答位变量
}


						/********操作部分代码*********/
//#include "MPU6050_Reg.h"          //硬件地址库
//#define MPU6050_ADDRESS		0xD0		//MPU6050的I2C从机地址
//
///**
//  * 函    数：硬件I2C等待事件
//  * 参    数：同I2C_CheckEvent
//  * 返 回 值：无
//  */
//void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
//{
//	uint32_t Timeout;
//	Timeout = 10000;									//给定超时计数时间
//	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)	//循环等待指定事件
//	{
//		Timeout --;										//等待时，计数值自减
//		if (Timeout == 0)								//自减到0后，等待超时
//		{
//			/*超时的错误处理代码，可以添加到此处*/
//			break;										//跳出等待，不等了
//		}
//	}
//}

///**
//  * 函    数：MPU6050写寄存器
//  * 参    数：RegAddress 寄存器地址，范围：参考MPU6050手册的寄存器描述
//  * 参    数：Data 要写入寄存器的数据，范围：0x00~0xFF
//  * 返 回 值：无
//  */
//void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
//{
//	/**********软件I2C部分代码**********/	
//	MyI2C_Start();						//I2C起始
//	MyI2C_SendByte(MPU6050_ADDRESS);	//发送从机地址，读写位为0，表示即将写入
//	MyI2C_ReceiveAck();					//接收应答
//	MyI2C_SendByte(RegAddress);			//发送寄存器地址
//	MyI2C_ReceiveAck();					//接收应答
//	MyI2C_SendByte(Data);				//发送要写入寄存器的数据
//	MyI2C_ReceiveAck();					//接收应答
//	MyI2C_Stop();						//I2C终止
//	
//	
//		/**********硬件I2C部分代码**********/	
////	I2C_GenerateSTART(I2C2, ENABLE);										//硬件I2C生成起始条件
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5
////	
////	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);	//硬件I2C发送从机地址，方向为发送
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//等待EV6
////	
////	I2C_SendData(I2C2, RegAddress);											//硬件I2C发送寄存器地址
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);			//等待EV8
////	
////	I2C_SendData(I2C2, Data);												//硬件I2C发送数据
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//等待EV8_2
////	
////	I2C_GenerateSTOP(I2C2, ENABLE);											//硬件I2C生成终止条件
//}

///**
//  * 函    数：MPU6050读寄存器
//  * 参    数：RegAddress 寄存器地址，范围：参考MPU6050手册的寄存器描述
//  * 返 回 值：读取寄存器的数据，范围：0x00~0xFF
//  */
//uint8_t MPU6050_ReadReg(uint8_t RegAddress)
//{
//	/**********软件I2C部分代码**********/	
//	uint8_t Data;
//	
//	MyI2C_Start();						//I2C起始
//	MyI2C_SendByte(MPU6050_ADDRESS);	//发送从机地址，读写位为0，表示即将写入
//	MyI2C_ReceiveAck();					//接收应答
//	MyI2C_SendByte(RegAddress);			//发送寄存器地址
//	MyI2C_ReceiveAck();					//接收应答
//	
//	MyI2C_Start();						//I2C重复起始
//	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);	//发送从机地址，读写位为1，表示即将读取
//	MyI2C_ReceiveAck();					//接收应答
//	Data = MyI2C_ReceiveByte();			//接收指定寄存器的数据
//	MyI2C_SendAck(1);					//发送应答，给从机非应答，终止从机的数据输出
//	MyI2C_Stop();						//I2C终止
//	
//	return Data;
//	
//	
//	/**********硬件I2C部分代码**********/	
////uint8_t Data;
////	
////	I2C_GenerateSTART(I2C2, ENABLE);										//硬件I2C生成起始条件
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5
////	
////	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);	//硬件I2C发送从机地址，方向为发送
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//等待EV6
////	
////	I2C_SendData(I2C2, RegAddress);											//硬件I2C发送寄存器地址
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//等待EV8_2
////	
////	I2C_GenerateSTART(I2C2, ENABLE);										//硬件I2C生成重复起始条件
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5
////	
////	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);		//硬件I2C发送从机地址，方向为接收
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);		//等待EV6
////	
////	I2C_AcknowledgeConfig(I2C2, DISABLE);									//在接收最后一个字节之前提前将应答失能
////	I2C_GenerateSTOP(I2C2, ENABLE);											//在接收最后一个字节之前提前申请停止条件
////	
////	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);				//等待EV7
////	Data = I2C_ReceiveData(I2C2);											//接收数据寄存器
////	
////	I2C_AcknowledgeConfig(I2C2, ENABLE);									//将应答恢复为使能，为了不影响后续可能产生的读取多字节操作
////	
////	return Data;
//}

///**
//  * 函    数：MPU6050获取ID号
//  * 参    数：无
//  * 返 回 值：MPU6050的ID号
//  */
//uint8_t MPU6050_GetID(void)
//{
//	return MPU6050_ReadReg(MPU6050_WHO_AM_I);		//返回WHO_AM_I寄存器的值
//}
