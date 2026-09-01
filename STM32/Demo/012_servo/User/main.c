#include "stm32f10x.h"                  // Device header
#include "NVIC.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"
uint16_t count=0;
int main(void){
	
    //标准库驱动
	//实现舵机驱动
	//调整pwm波形
	//初始化OLED
	OLED_Init();
	//初始化LED
    //初始化按键
	BUTTON_Init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_1);
	//初始化舵机
	SERVO_Init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_1);
	//打开定时器TIM时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//配置定时器为内部时钟
	TIM_InternalClockConfig(TIM2);
	//初始化TIMX的时间基数单元
	//定义专属结构
	//舵机特性周期固定20ms
	//高电平脉宽规定范围:0.5ms ~ 2.5ms（对应 0° ~ 180°）
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	//自动重载寄存器，arr
    TIM_TimeBaseInitStructure.TIM_Period=19999;
	//预分频器psc
    TIM_TimeBaseInitStructure.TIM_Prescaler= 71;
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
	//ccr默认值，90度
	TIM_OCInitStructure.TIM_Pulse=500;
	//记录
	count=TIM_OCInitStructure.TIM_Pulse;
	//通过更改ccr的值，改变舵机角度通道根据选择的引脚
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	//使能TIMX
	TIM_Cmd(TIM2,ENABLE);
	//复位
	SERVO_SetAngle(0);
	//angle
	OLED_ShowString(1,1,"angle:");
	while(1){
		//检测到低电位
		if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
			//防止一直按键
			while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){}
			//调节舵机角度,按一下加10度
			if(count>=180) count=0;
			count+=50;
			SERVO_SetAngle(count);
            Delay_ms(500);
		 
		}
		//angle
		 OLED_ShowNum( 2,1,count,8);
		//CCR
		 OLED_ShowNum( 3,1,TIM_GetCapture2(TIM2),8);
		//CNT
		 OLED_ShowNum( 4,1,TIM_GetCounter(TIM2),8);
 
 
	}
	
}
 


	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;