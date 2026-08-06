#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void){
	
    //标准库驱动
	//打开GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	while(1){
		//置低电平
		// GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		// Delay_s(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		// Delay_s(1);
	}
	
}



	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;