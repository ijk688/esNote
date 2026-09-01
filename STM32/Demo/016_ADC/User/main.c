#include "stm32f10x.h"                  // Device header
#include "OncPeripheral.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"

uint16_t ad0,ad1,ad2,ad3;
//电压数字信号值
uint16_t getvalue(uint8_t ADC_Channel){
	//配置adc规则组
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);
	//软件层面的手动触发
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	//轮询等待转换结束的标志信号
	while(!ADC_GetFlagStatus( ADC1,ADC_FLAG_EOC));
	//返回转换成功后的采样值
	return ADC_GetConversionValue(ADC1);         

}
 
int main(void){
    //使用ADC即模数转换器，将模拟信号转成数字信号
	//目标使用ADC显示引脚端电压
    //标准库驱动
	//开启ADC以及GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//开启adcclick时钟，选择六分频
     RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//初始化OLED
	OLED_Init();
	//初始化引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	//adc专属模式，gpio口直接接受模拟信号
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
 
 
 
	//初始化结构体
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;
	// ADC_StructInit(&ADC_InitStructure);
	//整体初始化
	ADC_Init(ADC1, &ADC_InitStructure);
	//通电即使能
	ADC_Cmd( ADC1, ENABLE);

	//运行后校准
	//复位校准寄存器
	ADC_ResetCalibration( ADC1);
	//获取校准复位标志状态
    while(ADC_GetResetCalibrationStatus( ADC1) );
    //启动校准
   ADC_StartCalibration(ADC1);
    //检查校准是否完成
    while(ADC_GetCalibrationStatus( ADC1) );

 
	OLED_ShowString(1,1,"ad0:");	
	OLED_ShowString(2,1,"ad1:");	
	OLED_ShowString(3,1,"ad2:");	
	OLED_ShowString(4,1,"ad3:");
	//输出
	while(1){
   ad0=getvalue(ADC_Channel_0);
    ad1=getvalue(ADC_Channel_1);
	 ad2=getvalue(ADC_Channel_2);
	  ad3=getvalue(ADC_Channel_3);
	OLED_ShowNum(1,6,ad0 ,4);
	OLED_ShowNum(2,6,ad1,4);
	OLED_ShowNum(3,6, ad2,4);
	OLED_ShowNum(4,6,ad3,4);
	}
	
}
 
 
 