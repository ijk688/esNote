#include "stm32f10x.h"                  // Device header
#include "NVIC.h"
#include "OLED.h"

uint32_t count=0;
int main(void){
	
    //标准库驱动

	//初始化OLED
	OLED_Init();
	//实现定时中断，即达到设定时间程序发生中断
	//打开定时器TIM时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//配置定时器为内部时钟
	TIM_InternalClockConfig(TIM2);
	//初始化TIMX的时间基数单元
	//定义专属结构
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period=9999;
    TIM_TimeBaseInitStructure.TIM_Prescaler= 7199;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStructure);
 
	//防止初始化即进入中断
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//使能指定的TIMx中断
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
    //配置NVIC优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//初始化NVIC
    Nvic_Init();
	//使能TIMX
	TIM_Cmd(TIM2,ENABLE);
	//编写中断函数
	//输出中断次数
	OLED_ShowString( 1,1, "INTERRUPT:" );
	while(1){
 
        OLED_ShowNum( 2,1,count,8);
		//显示计时器的值
		 OLED_ShowNum( 3,1,TIM_GetCounter(TIM2),8);
		 
	}
	
}
void TIM2_IRQHandler(void){
	//检查中断标志位
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		count++;
		//清楚中断标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}


	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;