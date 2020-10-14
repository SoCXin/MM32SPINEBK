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
    Dac1_Init();
    //上电后，使用示波器测量PA4波形
    while(1)
    {
        /* Start DAC Channel1 conversion by software */
        DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
    }
}


























