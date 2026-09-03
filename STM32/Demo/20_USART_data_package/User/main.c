#include "stm32f10x.h"                  
#include "OncPeripheral.h"
#include "OLED.h"
#include "Hardware.h"
#include "Delay.h"
#include <stdio.h>
#include <string.h>

 uint32_t arr1[4]={0x01,0x02,0x03,0x04};
 uint32_t receiveArr[4]={0};
 char receiveString[100];
 
 int fputc(int ch,FILE* f) {
    usart_sendnum(ch);
    return ch;
}
int main(void){
	//控制按钮收发数据包
    //标准库驱动
	//开启GPIOAB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
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
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //LED默认熄灭
     GPIO_SetBits(GPIOA,GPIO_Pin_1);
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

   //定义灯泡状态量
	while(1){
        //持续输出当前LED状态
        OLED_ShowString(1,1,"STATE:");
        //默认关闭状态
        OLED_ShowString(1,7,"LED_OFF");
		//比较指令
        //展示接受指令
        OLED_ShowString(2,1,"RECEIVE:");
        OLED_ShowString(2,9,receiveString);
         if(!strcmp(receiveString,"LED_OFF")){
            //更新LED状态
            usart_sendstring("LED_OFF");
            OLED_ShowString(1,7,"LED_OFF");
            GPIO_SetBits(GPIOA,GPIO_Pin_1);
            receiveString[0]='\0';
         }
         else if(!strcmp(receiveString,"LED_ON")){
            //更新LED状态
            usart_sendstring("LED_ON");
            OLED_ShowString(1,7,"LED_ON");
            GPIO_ResetBits(GPIOA,GPIO_Pin_1);
              receiveString[0]='\0';
         }
 //按键发送数据包
//    if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
//     while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));
//     //松开计数
//     usart_sendtxtdpack("hello,jk");
//             count++;
//             OLED_ShowNum(1,1,count,4);
//         }
	
}
}
//接受hex数据包
//  void USART1_IRQHandler(void) {

//         if(USART_GetFlagStatus( USART1, USART_FLAG_RXNE)){
//         //定义静态状态量
//         static uint8_t receiveState=0;
//         uint32_t receiveData= USART_ReceiveData(USART1);
//         //数组位置
//         static uint8_t p=0;
//         //状态量为0
//         if(receiveState==0){
//             //起始位标志
//             if(receiveData==0xFF){
//              //改变状态量
//              receiveState=1;
//              //初始化位置
//              p=0;
//             }
//         }
//         //接受数据状态
//        else if(receiveState==1){
//             //结束标志为收到四个数据
//             if(p<4){
//             receiveArr[p]=receiveData;
//             p++;
//             }
//             //改变状态量
//             else  receiveState=2;
//         }
//        else if(receiveState==2){
//             //结束位标志
//             if(receiveData==0xFE){
//              //改变状态量
//              receiveState=0;
//             }
//         }
//      }
//         }
//接受文本数据包
 void USART1_IRQHandler(void) {

        if(USART_GetFlagStatus( USART1, USART_FLAG_RXNE)){
        //定义静态状态量
        static uint8_t receiveState=0;
         static uint8_t p=0;
        char receiveData= USART_ReceiveData(USART1);
        //状态量为0
        if(receiveState==0){
            //起始位标志
            if(receiveData=='@'){
             //改变状态量
             receiveState=1;
             p=0;
             //初始化接受字符串
            receiveString[p]= '\0';
            }
        }
        //接受数据状态
       else if(receiveState==1){
           //结束标志
            if(receiveData=='\r'){
             //改变状态量
             receiveState=2;
            }
            else{
               receiveString[p]= receiveData;
               p++;
            }
        }
       else if(receiveState==2){
            //结束位标志
            if(receiveData=='\n'){
             receiveString[p]= '\0';
             //改变状态量
             receiveState=0;
            }
        }
     }

    }
    
 