#include "stm32f10x.h"                  // Device header
#include "NVIC.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"
uint32_t count=0;
int main(void){
	
    //标准库驱动
	//实现呼吸灯
	//调整pwm波形
	//初始化OLED
	OLED_Init();
	//初始化LED
    //a0口的复用与定时器的输出联系起来
	//引脚重映射
	//开启AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//部分重映射
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
	//关闭默认的调试端口服用
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    LED_Init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_15);
	//打开定时器TIM时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//配置定时器为内部时钟
	TIM_InternalClockConfig(TIM2);
	//初始化TIMX的时间基数单元
	//定义专属结构
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	//自动重载寄存器，arr
    TIM_TimeBaseInitStructure.TIM_Period=99;
	//预分频器psc
    TIM_TimeBaseInitStructure.TIM_Prescaler= 719;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStructure);
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
	//ccr
	TIM_OCInitStructure.TIM_Pulse=50;
	//通过更改ccr的值，可以让led保持不同的亮度，进而达到呼吸灯的效果
	 
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	//使能TIMX
	TIM_Cmd(TIM2,ENABLE);
	//使能通道输出
	TIM_CCxCmd(TIM2,TIM_Channel_1,TIM_CCx_Enable);
    //输出运行时间
	int i=0;
	while(1){
		for(i=0;i<=100;i++){
		TIM_SetCompare1(TIM2, i);
		Delay_ms(10);
		count++;
		OLED_ShowString(1,1,"time:");
        OLED_ShowNum( 2,1,count,8);
		//CNT
		OLED_ShowNum( 3,1,TIM_GetCounter(TIM2),8);
		//CCR
		OLED_ShowNum( 4,1,TIM_GetCapture1(TIM2),8);
		}
		for(i=0;i<=100;i++){
		TIM_SetCompare1(TIM2, (100-i));
		Delay_ms(10);
		count++;
		OLED_ShowString(1,1,"time:");
        OLED_ShowNum( 2,1,count,8);
		//CNT
		OLED_ShowNum( 3,1,TIM_GetCounter(TIM2),8);
		//CCR
		OLED_ShowNum( 4,1,TIM_GetCapture1(TIM2),8);
		}

 
	}
	
}
 


	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;