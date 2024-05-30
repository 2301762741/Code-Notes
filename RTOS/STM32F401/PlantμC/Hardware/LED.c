//#inclue "System.h"
#include "stm32f4xx.h"   

void GPIO_LED2int()
{
	RCC->AHB1ENR=RCC->AHB1ENR|1;//´ò¿ªGPIOAµÄÊ±ÖÓ£¬ÒÔ¿ªÊ¼²Ù×÷¼Ä´æÆ÷£¬ÅäÖÃGPIO¿Ú
	GPIOA->MODER=GPIOA->MODER&~(3<<10);//ÅäÖÃ¼Ä´æÆ÷£¬µ«ÊÇ¼Ä´æÆ÷×´Ì¬²»ÎÈ¶¨£¬ËùÒÔÐèÒªÏÈÇåÁã¡£²é±í¿ÉÖª£¬PA5¿ÚÔÚMODER5£¨&~±£Ö¤ÆäËûÎ»1¡¢0×´Ì¬²»±ä£©
	GPIOA->MODER=GPIOA->MODER|(1<<10);//µãµÆÐèÒª´ò¿ªÍ¨ÓÃÊä³öÄ£Ê½£¬¶ÔÓ¦¼Ä´æÆ÷×´Ì¬²é±í¿ÉÖª£¬01ÎªÍ¨ÓÃÊä³öÄ£Ê½
	GPIOA->OTYPER=GPIOA->OTYPER&~(1<<5);//½«Êä³öÀàÐÍ¼Ä´æÆ÷ÉèÖÃÎªÍÆÍìÄ£Ê½£¬´ËÊ±Ö»ÐèÒª°Ñ¼Ä´æÆ÷ÇåÁã
	GPIOA->OSPEEDR=GPIOA->OSPEEDR&~(3<<10);//ÇåÁã
	GPIOA->OSPEEDR=GPIOA->OSPEEDR|(2<<10);//Ò»°ãÀ´Ëµ£¬Êä³ö×´Ì¬³£ÓÃ¸ßËÙ
	GPIOA->PUPDR=GPIOA->PUPDR&~(3<<10);//ÕâÀïÐèÒªµÄÊÇ¸¡¿ÕÄ£Ê½£¬Ö±½ÓÇåÁã¾ÍºÃ
	GPIOA->ODR=GPIOA->ODR|(1<<5);//Ò»°ãÉèÖÃÎª1Ê±Êä³ö¸ßµçÆ½£¬µÆÃð
	
	GPIOA->MODER=GPIOA->MODER&~(3);//ÅäÖÃ¼Ä´æÆ÷£¬µ«ÊÇ¼Ä´æÆ÷×´Ì¬²»ÎÈ¶¨£¬ËùÒÔÐèÒªÏÈÇåÁã¡£²é±í¿ÉÖª£¬PA5¿ÚÔÚMODER5£¨&~±£Ö¤ÆäËûÎ»1¡¢0×´Ì¬²»±ä£©
	GPIOA->MODER=GPIOA->MODER|1;//µãµÆÐèÒª´ò¿ªÍ¨ÓÃÊä³öÄ£Ê½£¬¶ÔÓ¦¼Ä´æÆ÷×´Ì¬²é±í¿ÉÖª£¬01ÎªÍ¨ÓÃÊä³öÄ£Ê
	GPIOA->OTYPER=GPIOA->OTYPER&0;//½«Êä³öÀàÐÍ¼Ä´æÆ÷ÉèÖÃÎªÍÆÍìÄ£Ê½£¬´ËÊ±Ö»ÐèÒª°Ñ¼Ä´æÆ÷ÇåÁã
	GPIOA->OSPEEDR=GPIOA->OSPEEDR&~(3);//ÇåÁã
	GPIOA->OSPEEDR=GPIOA->OSPEEDR|(2);//Ò»°ãÀ´Ëµ£¬Êä³ö×´Ì¬³£ÓÃ¸ßËÙ
	GPIOA->PUPDR=GPIOA->PUPDR&~(3);//ÕâÀïÐèÒªµÄÊÇ¸¡¿ÕÄ£Ê½£¬Ö±½ÓÇåÁã¾ÍºÃ
	GPIOA->ODR=GPIOA->ODR|(1);//Ò»°ãÉèÖÃÎª1Ê±Êä³ö¸ßµçÆ½£¬µÆÃð
}

void LED_ON(void)
{
	GPIOA->ODR=GPIOA->ODR|(1<<5);//Ò»°ãÉèÖÃÎª1Ê±Êä³ö¸ßµçÆ½£¬µÆÃð
}

void LED_OFF(void)
{
	GPIOA->ODR=GPIOA->ODR&~(1<<5);//ÇåÁã£¬ÉèÖÃÎª0£¬µÍµçÆ½£¬µÆÁÁ(Ç°ÃæÓÐ~£¬·´Âë£¬±ä0ÐèÒªÓÃ1£©
}
