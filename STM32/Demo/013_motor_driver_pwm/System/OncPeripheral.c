#include "OncPeripheral.h"


void TIM_Init(void){
    //打开定时器TIM时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//配置定时器为内部时钟
	TIM_InternalClockConfig(TIM2);
	//初始化TIMX的时间基数单元
	//定义专属结构
	//采用10 kHz电机
	//ARR=99，CCR 取值范围：0 ~ 99
    // CCR=0：占空比 0%，电机不转
    // CCR=99：占空比 100%，满速
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	//自动重载寄存器，arr
    TIM_TimeBaseInitStructure.TIM_Period=99;
	//预分频器psc
    TIM_TimeBaseInitStructure.TIM_Prescaler=71;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	//初始化输出比较模式
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//赋初始值，下方修改所需要的值
	TIM_OCStructInit(&TIM_OCInitStructure);
	// TIM_OCInitStructure.TIM_OCIdleState=;
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	// TIM_OCInitStructure.TIM_OCNIdleState;
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
	// TIM_OCInitStructure.TIM_OCNPolarity;
	//TIM_OCInitStructure.TIM_OutputNState;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	//ccr默认值
	TIM_OCInitStructure.TIM_Pulse=0;
	//根据引脚决定
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	//使能TIMX
	TIM_Cmd(TIM2,ENABLE);
}
void Exit_Init(void){
     EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
}
void Nvic_Init(void){
    NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure);
    
    // NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn    ;
	// NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
    // NVIC_Init(&NVIC_InitStructure);
}
