#include "stm32f10x.h"                  
#include "OncPeripheral.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"

uint32_t ad1[4];
//电压数字信号值
 
 
int main(void){
	//使用DMA来完成数据转运
	//使用ADC即模数转换器，将模拟信号转成数字信号
	//目标使用ADC显示引脚端电压
    //标准库驱动
	//开启DADC以及GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//开启adcclick时钟，选择六分频
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	//开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
	//初始化OLED
	OLED_Init();

	//初始化DMA
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_BufferSize=4;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)ad1;
	DMA_InitStructure.DMA_MemoryDataSize= DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode= DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;;
	DMA_InitStructure.DMA_Priority= DMA_Priority_High;
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);
    //初始化引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	//adc专属模式，gpio口直接接受模拟信号
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
 
	//初始化结构体
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel=4;
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;
	// ADC_StructInit(&ADC_InitStructure);
	//整体初始化
	ADC_Init(ADC1, &ADC_InitStructure);
	//配置adc规则组
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
			ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
				ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	//开启DMA
    DMA_Cmd(DMA1_Channel1, ENABLE);	 
	//通电即使能
	ADC_Cmd( ADC1, ENABLE);
	//开启adc的DMA请求
    ADC_DMACmd(ADC1,ENABLE);
	//运行后校准
	//复位校准寄存器
	ADC_ResetCalibration( ADC1);
	//获取校准复位标志状态
    while(ADC_GetResetCalibrationStatus( ADC1) );
    //启动校准
    ADC_StartCalibration(ADC1);
    //检查校准是否完成
    while(ADC_GetCalibrationStatus( ADC1) );
	//软件层面的手动触发
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	OLED_ShowString(1,1,"ad10:");	
	OLED_ShowString(2,1,"ad11:");	
	OLED_ShowString(3,1,"ad12:");	
	OLED_ShowString(4,1,"ad13:");
	//输出
	while(1){
   for(int i=0;i<4;i++){
	OLED_ShowNum(i+1,6,ad1[i],4);
   }
	}
	
}
 
 
 