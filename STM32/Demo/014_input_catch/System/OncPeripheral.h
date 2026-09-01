#ifndef _EXIT_H
#define _EXIT_H

#include "stm32f10x.h"    

void GPIOA_Init(GPIO_InitTypeDef GPIO_InitStructure);
void TIM_Init(void);
void Exit_Init(void);
void Nvic_Init(void);
#endif