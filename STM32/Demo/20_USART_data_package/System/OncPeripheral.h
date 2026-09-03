#ifndef _EXIT_H
#define _EXIT_H

#include "stm32f10x.h"    
void usart_sendarray(uint32_t* arr,int num);
void usart_sendnum(uint32_t num);
void usart_sendstring(char* string);
 
void usart_sendhexdpack(uint32_t* arr);
void usart_sendtxtdpack(char* string);
void GPIOA_Init(GPIO_InitTypeDef GPIO_InitStructure);
void TIM_Init(void);
void Exit_Init(void);
void Nvic_Init(void);
#endif