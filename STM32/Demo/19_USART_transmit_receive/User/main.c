#include "stm32f10x.h"                  
#include "OncPeripheral.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"
#include <stdio.h>

void usart_sendnum(uint32_t num){
 //发送数据
 USART_SendData(USART1,num);
 //等待发送结束
 while(!USART_GetFlagStatus( USART1, USART_FLAG_TC));
}
void usart_sendstring(char* string){
    char* p=string;
    while(*p!='\0'){
    //发送数据
    USART_SendData(USART1,*p);
     //等待发送结束
    while(!USART_GetFlagStatus( USART1, USART_FLAG_TC));
     p++;
    }
}
int fputc(int ch,FILE* f) {
    usart_sendnum(ch);
    return ch;
}
 
int main(void){
	//使用USART完成串口发送
 
    //标准库驱动
	//开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//开启USART时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//初始化OLED
	OLED_Init();

    //初始化引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	//初始化USART
	USART_InitTypeDef USART_InitStructure;
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate=9600;
   USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None ;
   USART_InitStructure.USART_Mode=USART_Mode_Tx |USART_Mode_Rx ;
   USART_InitStructure.USART_WordLength=USART_WordLength_8b ;
   USART_InitStructure.USART_StopBits=USART_StopBits_1   ;
   USART_InitStructure.USART_Parity=USART_Parity_No ;
    USART_Init( USART1,&USART_InitStructure);
    //启动USART
   USART_Cmd( USART1,ENABLE);
   Nvic_Init();
   //开启中断
   USART_ITConfig( USART1, USART_IT_RXNE, ENABLE);

   //中断函数
 uint32_t i=0;
	//输出
	while(1){
        //显示接收到的数据
        // if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)){
        //   OLED_ShowNum(1,1,USART_ReceiveData(USART1),4);
        // }
    // usart_sendstring("hello,jk!");
//  printf("hello jk!\r\n");
//  i++;
//    OLED_ShowString(1,1,"transmited:");
//  OLED_ShowNum(1,12,i,4);
  //输出得到的数据
//   OLED_ShowNum(2,1,USART_ReceiveData(USART1),4);
//    Delay_s(1);
	}
	
}
 
 void USART1_IRQHandler(void) {
         //显示接收到的数据
        if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)){
          OLED_ShowNum(1,1,USART_ReceiveData(USART1),4);
        }
 }