#include "includes.h"
#include "os_trace_events.h"			//SystemView


MPU6050_DataTypeDef Acc_Gyro;	//原始加速度角速度数据
HMC5883L_DataTypeDef Mag;		//原始磁力数据
Float_t fGyro;					//角速度数据（弧度）

uint32_t PWM_IN_CH[4];			//4个输入捕获通道高电平计数值

uint8_t sendBuf[20];			//串口发送数据帧


/*	任务优先级	*/
#define TASK_STARTUP_PRIO	20
#define TASK_ANGEL_PRIO		21
#define TASK_MOTOR_PRIO		22
#define TASK_COM_PRIO		23
#define TASK_LED_PRIO		24

/*	任务栈大小	*/
#define TASK_STARTUP_STK_SIZE		128
#define TASK_ANGEL_STK_SIZE			128
#define TASK_MOTOR_STK_SIZE			128
#define TASK_COM_STK_SIZE			128
#define TASK_LED_STK_SIZE			64

/*	任务栈定义	*/
OS_STK	TASK_STARTUP_STK[TASK_STARTUP_STK_SIZE];
OS_STK	TASK_ANGEL_STK[TASK_ANGEL_STK_SIZE];
OS_STK	TASK_MOTOR_STK[TASK_MOTOR_STK_SIZE];
OS_STK  TASK_COM_STK[TASK_COM_STK_SIZE];
OS_STK	TASK_LED_STK[TASK_LED_STK_SIZE];

/*	任务	*/
void Task_Startup(void *pdata);
void Task_Angel(void *pdata);
void Task_Motor(void *pdata);
void Task_Com(void *pdata);
void Task_LED(void *pdata);

//OS_EVENT *sem;

//	sem = OSSemCreate(1);
//uint8_t i;
//int8_t buff[4];


int main(void){
	
	
	OSInit();
	OSTaskCreate(Task_Startup,(void *)0, &TASK_STARTUP_STK[TASK_STARTUP_STK_SIZE-1], TASK_STARTUP_PRIO);
	OSStart();
	
	return 0;
}


void Task_Startup(void *pdata){
	Delay_Init(84);			//Delay初始化
	SysTick_Init();			//滴答定时器初始化
	Serial_Init();			//串口初始化
	IIC_Init();				
	MPU6050_Init();
	HMC5883L_Init();
	PWM_Init();
	IC_Init();
	LED_Init();
	
	Motor_Start();
	OS_TRACE_INIT();
	OSTimeDlyHMSM(0,0,5,0);
	
	OSTaskCreate(Task_Angel,(void *)0, &TASK_ANGEL_STK[TASK_ANGEL_STK_SIZE-1], TASK_ANGEL_PRIO);
	OSTaskCreate(Task_Motor,(void *)0, &TASK_MOTOR_STK[TASK_MOTOR_STK_SIZE-1], TASK_MOTOR_PRIO);
	OSTaskCreate(Task_Com,(void *)0, &TASK_COM_STK[TASK_COM_STK_SIZE-1], TASK_COM_PRIO);
	OSTaskCreate(Task_LED,(void *)0,&TASK_LED_STK[TASK_LED_STK_SIZE-1],TASK_LED_PRIO);
	
	INT8U err;
	OSTaskNameSet(TASK_ANGEL_PRIO, (INT8U *)"Task_Angel", &err);
	OSTaskNameSet(TASK_MOTOR_PRIO, (INT8U *)"TASK_MOTOR", &err);
	OSTaskNameSet(TASK_COM_PRIO, (INT8U *)"TASK_COM", &err);
	OSTaskNameSet(TASK_LED_PRIO, (INT8U *)"TASK_LED", &err);
	
	OSTaskDel(OS_PRIO_SELF);
}




void Task_Angel(void *pdata){
	while(1){
		MPU6050_GetData();
		HMC5883L_GetData();
		OSTimeDly(1);
	}
}

void Task_Motor(void *pdata){
	while(1){
		PWM_OUT();
		OSTimeDly(3);
	}
}


void Task_Com(void *pdata){
	while(1){
		Send_Senser(Acc_Gyro.AccX,Acc_Gyro.AccY,Acc_Gyro.AccZ,Acc_Gyro.GyroX,Acc_Gyro.GyroY,Acc_Gyro.GyroZ,Mag.MagX,Mag.MagY,Mag.MagZ);
		OSTimeDly(10);
	}
}


void Task_LED(void *pdata){
	while(1){	
		LED_ON();
		OSTimeDlyHMSM(0, 0, 1, 0);
		LED_OFF();
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}


