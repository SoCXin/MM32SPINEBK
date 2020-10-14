#include "sys.h"
#include "uart.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "dac.h"
int main(void)
{
    delay_init();	    	 //延时函数初始化
    LED_Init();		  	 	//初始化与LED连接的硬件接口
    KEY_Init();          	//初始化与按键连接的硬件接口
    TIM2_Trig_DAC_Init();
    Dac1_Init();
    Dac2_Init();
    //上电后，使用示波器测量PA4、PA5波形

    DAC->CR |= DAC_CR_EN1; //DAC通道1使能
    DAC->CR |= ( DAC_CR_EN1 << 16 ); //DAC通道2使能

    DAC->DHR12RD |= 0x100;
    DAC->DHR12RD |= ( 0x100 << 16 );

    TIM2->CR1 |= 0x0001;
    while(1);
}


























