#include "System.h"      //#include "stm32f4xx.h"                  // Device header
#include "ucos_ii.h"

#define	TASK_STK_SIZE	 	 256     //定义堆栈长度
OS_STK LED0_TASK_STK[TASK_STK_SIZE];
OS_STK LED1_TASK_STK[TASK_STK_SIZE];  

void Main_Init(void);
void Task_LED0(void *pdada);
void Task_LED1(void *pdada);
int ce(int A,int B,int C) { return A+B+C;}

int main(void){
	
	int a=1,b=2,c=3;
	ce(a,b,c);
	
	
	
	Main_Init();
	GPIO_LED2int();
	
	OSTaskCreate(Task_LED1,(void *)0, &LED0_TASK_STK[TASK_STK_SIZE-1], 4);
    OSTaskCreate(Task_LED0,(void *)0, &LED1_TASK_STK[TASK_STK_SIZE-1], 5);
	OSStart();
    return 0;
}

void Main_Init(void){
	OSInit();
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);
}

void Task_LED0(void *pdada){
	
	while(1){
		//diandeng
		GPIOA->ODR=GPIOA->ODR&~(1<<5);//清零，设置为0，低电平，灯亮(前面有~，反码，变0需要用1）
		OSTimeDly(100);
		GPIOA->ODR=GPIOA->ODR|(1<<5);//一般设置为1时输出高电平，灯灭
		OSTimeDly(100);
	}
	
}

void Task_LED1(void *pdada){
	
	while(1){
		//guandeng
		//OSTimeDly(100);
		
		GPIOA->ODR=GPIOA->ODR&~(1);//清零，设置为0，低电平，灯亮(前面有~，反码，变0需要用1）
		OSTimeDly(100);
		GPIOA->ODR=GPIOA->ODR|(1);//一般设置为1时输出高电平，灯灭
		OSTimeDly(100);
		
	}
}
