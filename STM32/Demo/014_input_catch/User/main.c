#include "stm32f10x.h"                  // Device header
#include "OncPeripheral.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"
//计算频率
volatile uint32_t  PWM_Freq =0;
//计算占空比
volatile uint32_t PWM_Duty=0;
int main(void){
	//目标：利用定时器输入捕获功能实现输出频率以及占空比
    //输出波形在PA0该引脚仅支持TIM2_CH1，也就是TIM2定时器用于输出功能
	//输入捕获引脚为PA6仅支持TIM3_CH1
	//上升沿检测：使用直接模式引脚1直接捕获
	//下降沿检测：使用间接模式引脚2通过引脚1传递的信息捕获
	//由于需要模拟输入输出，所以需要两个时基单元
	//一个定时器只有一个时基单元，所以要初始化两个定时器
    //标准库驱动
	//初始化OLED
	OLED_Init();
	//初始化引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_Init(GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIOA_Init(GPIO_InitStructure);
	//打开定时器TIM2，TIM3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//配置定时器为内部时钟
	TIM_InternalClockConfig(TIM2);
	TIM_InternalClockConfig(TIM3);
	//初始化TIMX的时间基数单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	//自动重载寄存器，arr
    TIM_TimeBaseInitStructure.TIM_Period=99;
	//预分频器psc
    TIM_TimeBaseInitStructure.TIM_Prescaler=71;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	//TIM3
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	//自动重载寄存器，arr
    TIM_TimeBaseInitStructure.TIM_Period=65535;
	//预分频器psc
    TIM_TimeBaseInitStructure.TIM_Prescaler=17;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	//初始化为输入捕获模式
	//输出PWM波形信息需要同时捕获上升沿与下降沿，用到一种定时器的两种引脚
	TIM_ICInitTypeDef TIM3_IC1InitStructure;
	TIM_ICInitTypeDef TIM3_IC2InitStructure;
	//赋初始值，下方修改所需要的值
    TIM_ICStructInit(&TIM3_IC1InitStructure);
	//引脚2采用间接模式
	TIM_ICStructInit(&TIM3_IC2InitStructure);
	TIM3_IC2InitStructure.TIM_Channel = TIM_Channel_2;
	TIM3_IC2InitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
	TIM3_IC2InitStructure.TIM_ICSelection=TIM_ICSelection_IndirectTI;
	//TIM2
	//初始化输出比较模式
	TIM_OCInitTypeDef TIM2_OCInitStructure;
	//赋初始值，下方修改所需要的值
	TIM_OCStructInit(&TIM2_OCInitStructure);
	// TIM_OCInitStructure.TIM_OCIdleState=;
	TIM2_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	// TIM_OCInitStructure.TIM_OCNIdleState;
	TIM2_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;
	// TIM_OCInitStructure.TIM_OCNPolarity;
	//TIM_OCInitStructure.TIM_OutputNState;
	TIM2_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	//ccr默认值
	TIM2_OCInitStructure.TIM_Pulse=50;
	//根据引脚决定
	TIM_OC1Init(TIM2,&TIM2_OCInitStructure);
	TIM_ICInit(TIM3,&TIM3_IC1InitStructure);
	TIM_ICInit(TIM3,&TIM3_IC2InitStructure);
	//选择触发器TI1FP1
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	//从模式清零计数器CNT
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	//开启捕获中断
	TIM_ITConfig(TIM3,TIM_IT_CC1,ENABLE);
	//初始化NVIC
	 Nvic_Init();
	//使能TIMX
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	//输出
	while(1){
 	OLED_ShowString(1,1,"PWM_Freq:");
	OLED_ShowNum(2,1,PWM_Freq,10);
	OLED_ShowString(3,1,"PWM_Duty:");
	OLED_ShowNum(4,1,PWM_Duty,10);
	}
	
}

//中断函数
void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3,TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);
		uint16_t ccr1 = TIM_GetCapture1(TIM3);
		uint16_t ccr2 = TIM_GetCapture2(TIM3);
		PWM_Freq = 72000000 / 18 / (ccr1+1);
		PWM_Duty = 100 * (ccr2+1) / (ccr1+1);
 
	}
}
 