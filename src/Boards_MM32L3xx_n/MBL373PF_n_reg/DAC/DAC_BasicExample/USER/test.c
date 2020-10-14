#include "sys.h"
#include "uart.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "dac.h"
int main(void)
{
    u32 dacx;
    delay_init();	    	 //延时函数初始化
    LED_Init();		  	 	//初始化与LED连接的硬件接口
    KEY_Init();          	//初始化与按键连接的硬件接口
    Dac1_Init();
    //上电后，使用万用表测量PA4(Ain2)电压值，发现电压从0V不断网上递增，接近3.3V后又从头开始。
    while(1)
    {
        DAC->DHR12R1 = dacx;
        delay_ms(150);
        dacx = dacx + 200;
        if(dacx > 4095)
        {
            dacx = 0;
        }

    }
}


























