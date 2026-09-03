#include "stm32f10x.h"                  // Device header
#include "OncPeripheral.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"

uint32_t ad1[4]={1,2,3,4};
uint32_t ad2[4]={0};
 
 
int main(void){
    //使用DMA来完成数据转运
    //标准库驱动
	OLED_Init();
	//开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,  ENABLE);
	//初始化
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_BufferSize=4;
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;
	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)ad2;
	DMA_InitStructure.DMA_MemoryDataSize= DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable ;
	DMA_InitStructure.DMA_Mode= DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)ad1;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;;
	DMA_InitStructure.DMA_Priority= DMA_Priority_High;
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	//开启DMA
    DMA_Cmd(DMA1_Channel1, ENABLE);
    
	OLED_ShowString(1,1,"ad10:");	
	OLED_ShowString(2,1,"ad11:");	
	OLED_ShowString(3,1,"ad12:");	
	OLED_ShowString(4,1,"ad13:");
	OLED_ShowString(1,9,"ad20:");	
	OLED_ShowString(2,9,"ad21:");	
	OLED_ShowString(3,9,"ad22:");	
	OLED_ShowString(4,9,"ad23:");
	//输出
	while(1){
         for(int i=0;i<4;i++){
			ad1[i]++;
			OLED_ShowNum(i+1,6,ad1[i],2);
		 }
		 Delay_s(1);
		    for(int i=0;i<4;i++){
			OLED_ShowNum(i+1,15,ad2[i],2);
		 }
	}
	
}
 
 
 