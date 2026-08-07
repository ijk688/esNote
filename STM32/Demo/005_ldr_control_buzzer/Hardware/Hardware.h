#ifndef _HARDWARE_H
#define _HARDWARE_H

#include "stm32f10x.h"   

//函数声明
void LED_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void BUTTON_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void LDR_MODULE_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void BUZZER_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

#endif