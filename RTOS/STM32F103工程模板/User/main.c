#include <string.h>
#include "stm32f10x.h"                  // Device header
#include "System.h"


uint16_t num=0;
uint8_t zu[]={0x09,'A','B'};

char RxData[100];   //数据缓存

 // GPint(GPB,OutOD,P6);												//GPIO初始化
 //	GPIO_SetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为高电平
 // GPIO_ResetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为低电平
 //	GPIO_WriteBit(GPIOC, GPIO_Pin_14,0);
 //	GPIO_Write(GPIOA,0x0001);                     //将A整块寄存器地址设置 （上面引脚选择应为GPIO_Pin_ALL）
int main(void)
{
	OLED_Init();
	OLED_ShowString(1,7,"OLED");
	//EXTIint();
	
	//TIMint();
	//PWMint();
	//ICint();
	//ADint();					//AD初始化
	
//	USEint();
//	HCint();   
//	USE_SendString("OK!");
	
	//MyI2C_Init();
	//MySPI_Init();
	
//		W25Q64_Init();		  //W25Q64初始化
//		W25Q64_Show();      //读写操作展示    
	
		MyRTC_Init();		//RTC初始化
		OLED_ShowString(2, 1, "Date:XXXX-XX-XX");    //显示时间格式
		OLED_ShowString(3, 1, "Time:XX:XX:XX");
		OLED_ShowString(4, 1, "Being you,cheer!");

	//Music_TIM();
	
		//OLED_ShowHexNum(2,1,MyFLASH_ReadWord(0x08000F00),8);		//读取falsh
		//MyFLASH_EraseAllPages();   //擦除页，可加地址 0x08000000(第一页) 0x08000400(第二页)...
		//MyFLASH_ProgramWord(0x08000C00, 0x125);  //写入flash
//		Store_Init();     //上电保存flash里的数据至Store
//		Store_Data[10]=0x1234;
//		Store_Save();						/****还有问题*****/
//		//Store_Clear();
		
		
	while (1)
	{	
		//OLED_ShowNum(2,1,num,numlen(num));   //定时器触发
		//OLED_ShowNum(3,1,Tim_Count(),5);   //计数器计数次数
		//TIM_SetCounter(TIM2,FreqTable[FreqSelect]); //设置计数器开始值
		

		//huxiLED();         //PWM呼吸灯波形输出
		//OLED_ShowNum(2,1,IC_GetHZ(),numlen(IC_GetHZ()));  //ICpwd模电波形测频和测占空比
		
		//USE_SendByte(0x01);   //发送一个数据
		//USE_SendPacket(zu,sizeof(zu)/sizeof(zu[0])); //发送数据包,以FF开头，FE结尾
		//Delay_ms(500);

//		HC_GetData(RxData);    //获取蓝牙串口数据     
//		num=HC_Orde(RxData);     //使用蓝牙命令控制
//		__WFI();  //睡眠中断唤醒模式	
		//if(num == 1)
		//	huxiLED();
		
 		
		//W25Q64_PageProgram(0x000000,zu, 4);	//将写入数据的测试数组写入到W25Q64中
		//W25Q64_ReadData(0x000000, zu, 4);  //读取刚写入的测试数据到读取数据的测试数组中
		
		
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);		//开启PWR的时钟
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);		//开启BKP的时钟
//			PWR_BackupAccessCmd(ENABLE);/*备份寄存器访问使能*/   //使用PWR开启对备份寄存器的访问
//			
//			BKP_WriteBackupRegister(BKP_DR1,zu[0]++);	//写入测试数据到备份寄存器
//			zu[1] = BKP_ReadBackupRegister(BKP_DR1);		//读取备份寄存器的数据
//			OLED_ShowHexNum(2,1,zu[1],2);
		
		MyRTC_ReadTime();							//RTC数组获取取时间，最新的时间存储到MyRTC_Time数组中
		MyRTC_ShowTime();							//oled显示RTC数组中的时间
		
		//Music_FMQ_xun();
		//Music();
		//Music_FMQ(200,500);
		//Delay_ms(100);	

	///MusicTm();
	
//		IWDGint(IWDG_Prescaler_16,2499);             //设置1000ms的喂狗时长  T=0.025ms * Prescaler * ('Reload'+1)
//		Delay_ms(1200);								//设置喂狗间隔800ms
//		IWDG_ReloadCounter();					//重装计数器，喂狗
//		OLED_ShowString(1,7,"wLED");

			
	}	
	
}

//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//	{
//		num++;
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}


