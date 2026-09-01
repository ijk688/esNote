#include "stm32f10x.h"                  // Device header
#include "NVIC.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"
uint16_t count=0;
int main(void){
	
    //标准库驱动
	//实现pwm驱动电机
	//初始化OLED
	OLED_Init();
    //初始化按键
	BUTTON_Init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_1);
	//初始化电机
	MOTOR_Init();
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
	//记录
	count=TIM_OCInitStructure.TIM_Pulse;
	//通过更改ccr的值
	//根据引脚决定
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	//使能TIMX
	TIM_Cmd(TIM2,ENABLE);
	//停止旋转
	//TIM_SetCompare3(TIM2, 0);
	OLED_ShowString(1,1,"v:");
	while(1){
		//检测到低电位
		if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
			//防止一直按键
			while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){}
			//调节电机转速
			//TIM_SetCompare3(TIM2, -20);
			TIM_SetCompare3(TIM2,50);
			// if(count>=100) count=0;
			// count+=20;
			// TIM_SetCompare3(TIM2, count);
            // Delay_ms(50);
		}
		//count
		 OLED_ShowNum( 2,1,count,8);
		//CCR
		 OLED_ShowNum( 3,1,TIM_GetCapture3(TIM2),8);
		//CNT
		 OLED_ShowNum( 4,1,TIM_GetCounter(TIM2),8);
	}
	
}
 