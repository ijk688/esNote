#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"

int main(void){
	
    //标准库驱动
    
	//初始化OLED
    OLED_Init();
	//清空OLED
    OLED_Clear();
	int count=0;
// void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
// void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
// void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
// void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
// void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
// void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
	while(1){
		//打印字符
		//OLED_ShowChar(1, 1, 'A');
		//打印字符串
		// OLED_ShowString(2, 1,"HELLO,JK!");
		//打印数字
		 OLED_ShowSignedNum(1,1,count, 10);
		 count++;
	     Delay_s(1);
	}
	
}



	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;