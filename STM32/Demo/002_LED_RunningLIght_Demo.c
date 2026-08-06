#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void){
	
	//标准库驱动
    
	//打开GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
    
	//防止初始化后电平不稳定，全部置高电平
	//参数为oxFFFF,表示全部引脚
	GPIO_Write(GPIOA,0xFFFF);
	//操纵GPIO

	// //写入高电位
	// GPIO_WriteBit(GPIOA, GPIO_Pin_0,  Bit_SET);
	// //写入低电位
	// GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
    // //延时
	// Delay_s(1);
	uint16_t led_pin[8]={
        GPIO_Pin_0,
		GPIO_Pin_1,
		GPIO_Pin_2,
		GPIO_Pin_3,
		GPIO_Pin_4,
		GPIO_Pin_5,
		GPIO_Pin_6,
		GPIO_Pin_7,
	};
	uint16_t count=0;
	while(1){
	//LED流水灯逻辑
	//第一个亮延时1秒灭第二个亮延时1秒灭以此类推	 
	//过于麻烦，应该使用循环，但地址问题？
	//数组解决
	//write函数就根据赋值将所有引脚赋值
	//例如前八位11001100 就依次将前八位引脚赋值为11001100
	count=count%8;
	// 写入低电位
	GPIO_Write(GPIOA,~led_pin[count]);
	// GPIO_WriteBit(GPIOA, led_pin[count] , Bit_RESET);
	//延时
	Delay_ms(500);
	//写入高电位
	GPIO_Write(GPIOA,~led_pin[count]);
	// GPIO_WriteBit(GPIOA,led_pin[count],  Bit_SET);
    //延时
	Delay_ms(500);
	count++;
	}
	
}