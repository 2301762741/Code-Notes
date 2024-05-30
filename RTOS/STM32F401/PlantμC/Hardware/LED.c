//#inclue "System.h"
#include "stm32f4xx.h"   

void GPIO_LED2int()
{
	RCC->AHB1ENR=RCC->AHB1ENR|1;//��GPIOA��ʱ�ӣ��Կ�ʼ�����Ĵ���������GPIO��
	GPIOA->MODER=GPIOA->MODER&~(3<<10);//���üĴ��������ǼĴ���״̬���ȶ���������Ҫ�����㡣����֪��PA5����MODER5��&~��֤����λ1��0״̬���䣩
	GPIOA->MODER=GPIOA->MODER|(1<<10);//�����Ҫ��ͨ�����ģʽ����Ӧ�Ĵ���״̬����֪��01Ϊͨ�����ģʽ
	GPIOA->OTYPER=GPIOA->OTYPER&~(1<<5);//��������ͼĴ�������Ϊ����ģʽ����ʱֻ��Ҫ�ѼĴ�������
	GPIOA->OSPEEDR=GPIOA->OSPEEDR&~(3<<10);//����
	GPIOA->OSPEEDR=GPIOA->OSPEEDR|(2<<10);//һ����˵�����״̬���ø���
	GPIOA->PUPDR=GPIOA->PUPDR&~(3<<10);//������Ҫ���Ǹ���ģʽ��ֱ������ͺ�
	GPIOA->ODR=GPIOA->ODR|(1<<5);//һ������Ϊ1ʱ����ߵ�ƽ������
	
	GPIOA->MODER=GPIOA->MODER&~(3);//���üĴ��������ǼĴ���״̬���ȶ���������Ҫ�����㡣����֪��PA5����MODER5��&~��֤����λ1��0״̬���䣩
	GPIOA->MODER=GPIOA->MODER|1;//�����Ҫ��ͨ�����ģʽ����Ӧ�Ĵ���״̬����֪��01Ϊͨ�����ģ�
	GPIOA->OTYPER=GPIOA->OTYPER&0;//��������ͼĴ�������Ϊ����ģʽ����ʱֻ��Ҫ�ѼĴ�������
	GPIOA->OSPEEDR=GPIOA->OSPEEDR&~(3);//����
	GPIOA->OSPEEDR=GPIOA->OSPEEDR|(2);//һ����˵�����״̬���ø���
	GPIOA->PUPDR=GPIOA->PUPDR&~(3);//������Ҫ���Ǹ���ģʽ��ֱ������ͺ�
	GPIOA->ODR=GPIOA->ODR|(1);//һ������Ϊ1ʱ����ߵ�ƽ������
}

void LED_ON(void)
{
	GPIOA->ODR=GPIOA->ODR|(1<<5);//һ������Ϊ1ʱ����ߵ�ƽ������
}

void LED_OFF(void)
{
	GPIOA->ODR=GPIOA->ODR&~(1<<5);//���㣬����Ϊ0���͵�ƽ������(ǰ����~�����룬��0��Ҫ��1��
}
