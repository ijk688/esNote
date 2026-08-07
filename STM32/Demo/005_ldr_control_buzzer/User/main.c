#include "stm32f10x.h"                  // Device header
#include "Hardware.h"
#include "Delay.h"
int main(void){
	
    //标准库驱动
    LDR_MODULE_Init(RCC_APB2Periph_GPIOB,GPIOB, GPIO_Pin_13);
    BUZZER_Init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_12);

	//光模块控制蜂鸣器
	//挡住光模块蜂鸣器响
	//读取挡住信号，阻塞，置蜂鸣器为低电位，直至无遮挡，置蜂鸣器为高电位
	while(1){
		//判断光敏模块输出
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)){
		   while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)){
			   GPIO_ResetBits(GPIOB,GPIO_Pin_12);
               Delay_ms(500);
			   GPIO_SetBits(GPIOB,GPIO_Pin_12);
			   Delay_ms(500);
		   }
		   //直到无遮挡
		   GPIO_SetBits(GPIOB,GPIO_Pin_12);
		}
	}
	
}



	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;