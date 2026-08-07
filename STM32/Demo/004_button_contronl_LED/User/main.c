#include "stm32f10x.h"                  // Device header
#include "Hardware.h"
#include "Delay.h"

int main(void){
	
    //标准库驱动

	//初始化
	LED_Init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_1);
	LED_Init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_2);
	BUTTON_Init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_1);
	BUTTON_Init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_11);
    
	//按键控制：一个按键控制一盏LED，互不干涉
	//实现逻辑：全置高电位，按键按下置低电位，引脚检测低电位，置LED低电位，并保持不变
	while(1){
             //表示按键1按下
	          if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
                 //延时消抖
				 Delay_ms(20);
				 //防止按住不松
				//持续循环，直到松手
				while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){}
				//延时消抖
				 Delay_ms(20);
				//置与LED原电位相反值
				GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)));
				 }
                //表示按键2按下
	          if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)){
                 //延时消抖
				 Delay_ms(20);
				 //防止按住不松
				//持续循环，直到松手
				while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)){}
				//延时消抖
				 Delay_ms(20);
				//置与LED原电位相反值
				GPIO_WriteBit(GPIOA, GPIO_Pin_2, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)));
				 }
	}
	
}



	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;