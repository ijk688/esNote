#include "stm32f10x.h"                  // Device header
#include "Hardware.h"
#include "OLED.h"

//记录程序中断次数
int count=0;
int main(void){
	
    //标准库驱动
    //实现对射式红外传感器的外部中断功能
    //初始化外设
	//初始化OLED
	OLED_Init();
	//初始化红外传感器
    INFRARED_SENSOR_Init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_14);
	//初始化OLED
	OLED_Init();
	//初始化复用功能IO控制器AFIO
	//充当线路选择器的作用
	//打开AFIO时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//配置外部中断线路
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource14);
	//初始化EXIT口，外部中断事件控制器
	//定义专属结构
    EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
	//分配抢占和子优先级位数，否则后续定义不生效
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//初始化NVIC,嵌套中断向量列表控制器
	//定义专属结构
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=40;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure);
	//编写外部中断函数
	//中断函数

	OLED_ShowString(1 , 1 , "count:");
	while(1){
	//实时显示中断次数
	 OLED_ShowNum(1, 7, count,10);
		
	}
	
}
//硬件自动调度
void EXTI15_10_IRQHandler(void){
	//判断标志位
	if(EXTI_GetITStatus(EXTI_Line14)==SET){
		//标志位生效,中断开始
		count++;
		//清空标志位，结束中断
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}



	//寄存器驱动
	//RCC->APB2ENR=0x00000010;
	//GPIOC->CRH=0X00300000;
	//GPIOC->ODR=0x00002000;