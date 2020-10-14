/**
******************************************************************************
* @file    dac.c
* @author  AE Team
* @version V1.3.9
* @date    28/08/2019
* @brief   This file provides all the dac firmware functions.
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
#include "dac.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/********************************************************************************************************
**函数信息 ：DAC_Channel_Single(uint32_t DAC_Channel_x)
**功能描述 ：配置DAC为单通道软件触发
**输入参数 ：DAC_Channel_x ,x=1,2
**输出参数 ：无
********************************************************************************************************/
void DAC_Channel_Single(uint32_t DAC_Channel_x)
{
    DAC_InitTypeDef  DAC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
    /* GPIOA Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /*通道1对应IO口为PA4,通道2对应IO口为PA5,配置为模拟输入*/
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /* 配置为软件触发*/
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software ;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;

    DAC_Init(DAC_Channel_x, &DAC_InitStructure);

    DAC_Cmd(DAC_Channel_x, ENABLE);
}
/********************************************************************************************************
**函数信息 ：DAC_SoftwareTrigger_Data()
**功能描述 ：设置DAC指定通道数据并使用软件触发
**输入参数 ：DAC_Channel_x,DAC通道号,x=1,2
uiData 输入数据
**输出参数 ：无
********************************************************************************************************/
void DAC_SoftwareTrigger_Data(uint32_t DAC_Channel_x, uint16_t uiData)
{
    unsigned char ucFlag = 0;
    if(DAC_Channel_x == DAC_Channel_1)
    {
        ucFlag = 1;
        /*按填写的规则输入数据,当前选择为12位右对齐*/
        DAC_SetChannel1Data(DAC_Align_12b_R, uiData & 0xfff);
    }
    else if(DAC_Channel_x == DAC_Channel_2)
    {
        ucFlag = 1;
        DAC_SetChannel2Data(DAC_Align_12b_R, uiData & 0xfff);
    }
    if(ucFlag == 1)
    {
        DAC_SoftwareTriggerCmd(DAC_Channel_x, ENABLE);
    }
}

