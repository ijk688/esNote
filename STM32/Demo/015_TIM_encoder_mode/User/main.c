#include "stm32f10x.h"                  // Device header
#include "OncPeripheral.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"
//计算频率
  int32_t speed;
  int32_t before_place=0;
  int32_t current_place=0;
 
//计算占空比
 
int main(void){
    //目标：利用定时器的编码器模式来测量旋转编码器的旋转速度
	//其中旋转编码器旋转产生两个相位，分别为A相位，B相位
	//芯片引脚分别接受A相位与B相位波形，并通过硬件内部自动处理得到cnt
	//cnt指的是旋转编码器的位置
	//旋转速率即为相对位置除以固定一段时间，固定的一段时间从何而来
	//此时需要开启第二个定时器来定时
    //标准库驱动
	//初始化OLED
	OLED_Init();
	//初始化引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_Init(GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	GPIOA_Init(GPIO_InitStructure);
	//打开定时器TIM2，TIM3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//配置定时器为内部时钟
	//TIM3计时器的编码器模式将片外外设当作计数源无需配时钟源
	TIM_InternalClockConfig(TIM2);
	//初始化TIMX的时间基数单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	//自动重载寄存器，arr
    TIM_TimeBaseInitStructure.TIM_Period=9999;
	//预分频器psc
    TIM_TimeBaseInitStructure.TIM_Prescaler=7199;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	//TIM3
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	//自动重载寄存器，arr
    TIM_TimeBaseInitStructure.TIM_Period=10000;
	//预分频器psc
    TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	//TIM3初始化为编码器接口模式
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	//开启捕获中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//初始化NVIC
	 Nvic_Init();
	//使能TIMX
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
 
	//输出
	while(1){
		OLED_ShowString(1,1,"speed:");
    OLED_ShowSignedNum(2,1,speed,10);
		OLED_ShowString(3,1,"before");
    OLED_ShowSignedNum(4,1, before_place,10);
	}
	
}

//中断函数
void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	    current_place = TIM3->CNT;
	   int32_t delta =  current_place -  before_place;
        // 正向跨过 10000 -> 0
        if(delta > 5000)
        {
            delta -= 10001;
        }

        // 反向跨过 0 -> 10000
        else if(delta < -5000)
        {
            delta += 10001;
        }

        speed = delta;

        before_place = current_place;
	}
}
 