#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void){
	
	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;
	
	//标准库驱动：实现LED闪烁
	//打开对应时钟及操作与RCC相关的函数
	//GPIO为挂载到APB2总线外设，故使用该函数
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	//初始化GPIO
	//初始化需要定义一个标准结构体
	//这样初始化函数才能根据标准结构体地址加偏移量的方式
	//来控制相应外设的模式等等
	GPIO_InitTypeDef GPIO_InitStructure;
	//推挽输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	//LED接在系统板A0脚即GIOA口的0引脚
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//使用标准库函数控制GPIO口
	//置高电平
    // GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//置低电平
    // GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//写入低电平
	// GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	//写入高电平
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);

/*
	//LED闪烁
	//基本原理：亮一段时间，灭一段时间
	while(1){
	//写入低电平
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
    //延时函数
	// Delay_us(1);
	// Delay_ms(1);
	Delay_s(1);
	// 写入高电平
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	Delay_s(1);
	}
*/
while(1){}

	
}