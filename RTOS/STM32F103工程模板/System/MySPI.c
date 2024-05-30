#include "stm32f10x.h"                  // Device header

/*引脚配置层*/

/**
  * 函    数：SPI写SS引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入SS的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SS为低电平，当BitValue为1时，需要置SS为高电平
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);		//根据BitValue，设置SS引脚的电平
}

/**
  * 函    数：SPI写SCK引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入SCK的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SCK为低电平，当BitValue为1时，需要置SCK为高电平
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);		//根据BitValue，设置SCK引脚的电平
}

/**
  * 函    数：SPI写MOSI引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入MOSI的电平，范围0~0xFF
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置MOSI为低电平，当BitValue非0时，需要置MOSI为高电平
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);		//根据BitValue，设置MOSI引脚的电平，BitValue要实现非0即1的特性
}

/**
  * 函    数：I2C读MISO引脚电平
  * 参    数：无
  * 返 回 值：协议层需要得到的当前MISO的电平，范围0~1
  * 注意事项：此函数需要用户实现内容，当前MISO为低电平时，返回0，当前MISO为高电平时，返回1
  */
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);			//读取MISO电平并返回
}

/**
  * 函    数：SPI初始化
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，实现SS、SCK、MOSI和MISO引脚的初始化
  */
void MySPI_Init(void)
{
	 						/**********软件SPI初始化**********/	
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA4、PA5和PA7引脚初始化为推挽输出
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA6引脚初始化为上拉输入
	
	/*设置默认电平*/
	MySPI_W_SS(1);											//SS默认高电平
	MySPI_W_SCK(0);											//SCK默认低电平
	
	
						/**********硬件SPI初始化**********/	
//	/*开启时钟*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//开启SPI1的时钟
//	
//	/*GPIO初始化*/
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA4引脚初始化为推挽输出
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA5和PA7引脚初始化为复用推挽输出
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA6引脚初始化为上拉输入
//	
//	/*SPI初始化*/
//	SPI_InitTypeDef SPI_InitStructure;						//定义结构体变量
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//模式，选择为SPI主模式
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//方向，选择2线全双工
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//数据宽度，选择为8位
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		//先行位，选择高位先行
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;	//波特率分频，选择128分频
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				//SPI极性，选择低极性
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;			//SPI相位，选择第一个时钟边沿采样，极性和相位决定选择SPI模式0
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;				//NSS，选择由软件控制
//	SPI_InitStructure.SPI_CRCPolynomial = 7;				//CRC多项式，暂时用不到，给默认值7
//	SPI_Init(SPI1, &SPI_InitStructure);						//将结构体变量交给SPI_Init，配置SPI1
//	
//	/*SPI使能*/
//	SPI_Cmd(SPI1, ENABLE);									//使能SPI1，开始运行
//	
//	/*设置默认电平*/
//	MySPI_W_SS(1);											//SS默认高电平

}

/*协议层*/

/**
  * 函    数：SPI起始
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);				//拉低SS，开始时序
}

/**
  * 函    数：SPI终止
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);				//拉高SS，终止时序
}

/**
  * 函    数：SPI交换传输一个字节，使用SPI模式0
  * 参    数：ByteSend 要发送的一个字节
  * 返 回 值：接收的一个字节
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
					/**********软件SPI用法代码**********/	
	uint8_t i, ByteReceive = 0x00;					//定义接收的数据，并赋初值0x00，此处必须赋初值0x00，后面会用到
	
	for (i = 0; i < 8; i ++)						//循环8次，依次交换每一位数据
	{
		MySPI_W_MOSI(ByteSend & (0x80 >> i));		//使用掩码的方式取出ByteSend的指定一位数据并写入到MOSI线
		MySPI_W_SCK(1);								//拉高SCK，上升沿移出数据
		if (MySPI_R_MISO() == 1){ByteReceive |= (0x80 >> i);}	//读取MISO数据，并存储到Byte变量
																//当MISO为1时，置变量指定位为1，当MISO为0时，不做处理，指定位为默认的初值0
		MySPI_W_SCK(0);								//拉低SCK，下降沿移入数据
	}
	
	return ByteReceive;								//返回接收到的一个字节数据
	
						/**********硬件SPI代码**********/	
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);	//等待发送数据寄存器空
//	
//	SPI_I2S_SendData(SPI1, ByteSend);								//写入数据到发送数据寄存器，开始产生时序
//	
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);	//等待接收数据寄存器非空
//	
//	return SPI_I2S_ReceiveData(SPI1);								//读取接收到的数据并返回
}


/***********W25Q64使用示范***************/
///**
//  * 函    数：W25Q64写使能
//  * 参    数：无
//  * 返 回 值：无
//  */
//void W25Q64_WriteEnable(void)
//{
//	MySPI_Start();								//SPI起始
//	MySPI_SwapByte(W25Q64_WRITE_ENABLE);		//交换发送写使能的指令
//	MySPI_Stop();								//SPI终止
//}

///**
//  * 函    数：W25Q64等待忙
//  * 参    数：无
//  * 返 回 值：无
//  */
//void W25Q64_WaitBusy(void)
//{
//	uint32_t Timeout;
//	MySPI_Start();								//SPI起始
//	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);				//交换发送读状态寄存器1的指令
//	Timeout = 100000;							//给定超时计数时间
//	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)	//循环等待忙标志位
//	{
//		Timeout --;								//等待时，计数值自减
//		if (Timeout == 0)						//自减到0后，等待超时
//		{
//			/*超时的错误处理代码，可以添加到此处*/
//			break;								//跳出等待，不等了
//		}
//	}
//	MySPI_Stop();								//SPI终止
//}

///**
//  * 函    数：W25Q64页编程
//  * 参    数：Address 页编程的起始地址，范围：0x000000~0x7FFFFF
//  * 参    数：DataArray	用于写入数据的数组
//  * 参    数：Count 要写入数据的数量，范围：0~256
//  * 返 回 值：无
//  * 注意事项：写入的地址范围不能跨页
//  */
//void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
//{
//	uint16_t i;
//	
//	W25Q64_SectorErase(Address);  // 先擦除这个扇区         
//	W25Q64_WriteEnable();						//写使能
//	
//	MySPI_Start();								//SPI起始
//	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);		//交换发送页编程的指令
//	MySPI_SwapByte(Address >> 16);				//交换发送地址23~16位
//	MySPI_SwapByte(Address >> 8);				//交换发送地址15~8位
//	MySPI_SwapByte(Address);					//交换发送地址7~0位
//	for (i = 0; i < Count; i ++)				//循环Count次
//	{
//		MySPI_SwapByte(DataArray[i]);			//依次在起始地址后写入数据
//	}
//	MySPI_Stop();								//SPI终止
//	
//	W25Q64_WaitBusy();							//等待忙
//}

///**
//  * 函    数：W25Q64扇区擦除（4KB）
//  * 参    数：Address 指定扇区的地址，范围：0x000000~0x7FFFFF
//  * 返 回 值：无
//  */
//void W25Q64_SectorErase(uint32_t Address)
//{
//	W25Q64_WriteEnable();						//写使能
//	
//	MySPI_Start();								//SPI起始
//	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);	//交换发送扇区擦除的指令
//	MySPI_SwapByte(Address >> 16);				//交换发送地址23~16位
//	MySPI_SwapByte(Address >> 8);				//交换发送地址15~8位
//	MySPI_SwapByte(Address);					//交换发送地址7~0位
//	MySPI_Stop();								//SPI终止
//	
//	W25Q64_WaitBusy();							//等待忙
//}

///**
//  * 函    数：W25Q64读取数据
//  * 参    数：Address 读取数据的起始地址，范围：0x000000~0x7FFFFF
//  * 参    数：DataArray 用于接收读取数据的数组，通过输出参数返回
//  * 参    数：Count 要读取数据的数量，范围：0~0x800000
//  * 返 回 值：无
//  */
//void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
//{
//	uint32_t i;
//	MySPI_Start();								//SPI起始
//	MySPI_SwapByte(W25Q64_READ_DATA);			//交换发送读取数据的指令
//	MySPI_SwapByte(Address >> 16);				//交换发送地址23~16位
//	MySPI_SwapByte(Address >> 8);				//交换发送地址15~8位
//	MySPI_SwapByte(Address);					//交换发送地址7~0位
//	for (i = 0; i < Count; i ++)				//循环Count次
//	{
//		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	//依次在起始地址后读取数据
//	}
//	MySPI_Stop();								//SPI终止
//}
