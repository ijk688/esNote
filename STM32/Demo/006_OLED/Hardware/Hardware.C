#include "Hardware.h"
 
//初始化光模块
void LDR_MODULE_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    //打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);
    //初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    //上拉输出
    GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
    //输入模式无需speed
    // GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOx,&GPIO_InitStructure);
}
//初始化蜂鸣器
void BUZZER_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    //打开时钟
     RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);
    //初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOx,&GPIO_InitStructure);
    //置为高电平
    GPIO_SetBits(GPIOx,GPIO_Pin);
}
//初始化LED
void LED_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    //打开时钟
     RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);
    //初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOx,&GPIO_InitStructure);
    //置为高电平
    GPIO_SetBits(GPIOx,GPIO_Pin);
}

//初始化按键
void BUTTON_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
    //打开时钟
     RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);
    //初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
    //输入模式无需speed
    // GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOx,&GPIO_InitStructure);
}
