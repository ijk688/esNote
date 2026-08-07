#include "stm32f10x.h"                  // Device header
#include "Hardware.h"
#include "OLED.h"
#include"EXIT.h"
#include"NVIC.h"
//记录程序中断次数
int count=0;
int main(void){
	
    //标准库驱动
    //实现旋转编码器的中断计数
    //初始化外设
	//初始化OLED
	OLED_Init();
	//初始化旋转编码器
	ROTARY_ENCODERA_Init( GPIO_PortSourceGPIOB,GPIOB,GPIO_Pin_0);
    ROTARY_ENCODERB_Init(GPIO_PortSourceGPIOB,GPIOB,GPIO_Pin_1);
	 //打开时钟
     RCC_APB2PeriphClockCmd(GPIO_PortSourceGPIOB,ENABLE);
	//初始化复用功能IO控制器AFIO
	//充当线路选择器的作用
	//打开AFIO时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//配置外部中断线路
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource1);
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB,GPIO_PinSource0);
	//初始化EXIT口，外部中断事件控制器
    Exit_Init();
	//分配抢占和子优先级位数，否则后续定义不生效
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//初始化NVIC,嵌套中断向量列表控制器
	Nvic_Init();
	//编写外部中断函数
	//中断函数
	
	OLED_ShowString(1 , 1 , "count:");
	while(1){
	//实时显示中断次数
	 OLED_ShowSignedNum(2, 1, count,8);
		
	}
	
}
//硬件自动调度
void EXTI0_IRQHandler(void){
	//判断标志位
	if(EXTI_GetITStatus(EXTI_Line0)==SET){
	//进入中断
	//中断下降沿触发，检查b口电位为低电平,正转
	if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
		count--;
	}
	};
    //结束中断
	EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI1_IRQHandler(void){
	//判断标志位
	if(EXTI_GetITStatus(EXTI_Line1)==SET){
	//进入中断
	//中断下降沿触发，检查a口电位为低电平，反转
	if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)){
		count++;
	}
	};
    //结束中断
	EXTI_ClearITPendingBit(EXTI_Line1);
}


	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;