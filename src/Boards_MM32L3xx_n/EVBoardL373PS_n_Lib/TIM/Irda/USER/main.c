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
#include "delay.h"
#include "sys.h"
#include "uart.h"
#include "led.h"
#include "remote.h"
#include "lcdc.h"
int main(void)
{
    unsigned char vol[20];
    u8 key;
    u8 t = 0;
    u8 *str = 0;
    delay_init();	    	 //—” ±∫Ø ˝≥ı ºª
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// …Ë÷√÷–∂œ”≈œ»º∂∑÷◊È2
    uart_initwBaudRate(9600);	 	//¥Æø⁄≥ı ºªØŒ™9600
    Remote_Init();			//∫ÏÕ‚Ω” ’≥ı ºªØ
    LED_Init();		  		//≥ı ºªØ”ÎLED¡¨Ω”µƒ”≤º˛Ω”ø⁄

    initLCD();
    putStr(110, 20, 2, 1, "MM32 Dev Board");
    putStr(110, 40, 2, 1, "Irda TEST");
    putStr(110, 60, 2, 1, "@MindMotion");
    putStr(110, 80, 2, 1, "2016/09/02");
    putStr(110, 100, 2, 1, "SYMBOL:");
    while(1)
    {
        key = Remote_Scan();
        if(key)
        {
            switch(key)
            {
                case 0: str = "ERROR"; break;
                case 162: str = "POWER"; break;
                case 98: str = "UP"; break;
                case 2: str = "PLAY"; break;
                case 194: str = "RIGHT"; break;
                case 34: str = "LEFT"; break;
                case 224: str = "VOL-"; break;
                case 168: str = "DOWN"; break;
                case 144: str = "VOL+"; break;
                case 104: str = "1"; break;
                case 152: str = "2"; break;
                case 176: str = "3"; break;
                case 48: str = "4"; break;
                case 24: str = "5"; break;
                case 122: str = "6"; break;
                case 16: str = "7"; break;
                case 56: str = "8"; break;
                case 90: str = "9"; break;
                case 66: str = "0"; break;
                case 82: str = "DELETE"; break;
            }
            LED2 = !LED2;
            putStr(170, 100, 2, 1, "         ");
            putStr(170, 100, 2, 1, str);
        }
        else delay_ms(10);
        t++;
        if(t == 20)
        {
            t = 0;
            LED1 = !LED1;
        }
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

















