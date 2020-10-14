/**
******************************************************************************
* @file    main.c
* @author  AE Team
* @version V1.3.9
* @date    28/08/2019
* @brief   This file provides all the main firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/
#include "sys.h"
#include "delay.h"
#include "uart.h"
#include "dac.h"

void GPIO_Configuration(void);
/********************************************************************************************************
**函数信息 ：int main (void)
**功能描述 ：测量PA4电压值，电压以约0.4V逐渐增长,3.2V时又从0V开始递增
**输入参数 ：无
**输出参数 ：无
********************************************************************************************************/
int main(void)
{
    unsigned int uiDACData = 0;
    delay_init();	    	 //延时函数初始化
    /*DAC通道1初始化,为单通道软件触发模式*/
    DAC_Channel_Single(DAC_Channel_1) ;

    while(1)//无限循环
    {
        /*DAC通道1输出,电压以约0.4V逐渐增长,3.2V时又从0V开始递增*/
        DAC_SoftwareTrigger_Data(DAC_Channel_1, uiDACData);
        uiDACData += 500;
        if(uiDACData > 4095)
        {
            uiDACData = 0;
        }
        delay_ms(1000);
    }
}

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/

