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

#include "HAL_conf.h"
#include "HAL_device.h"
#include "stdio.h"

char printBuf[100];
void UartSendGroup(u8 *buf, u16 len);



void ECB_128_encry(uint8_t *Key, uint8_t *Input, uint32_t Ilength, uint8_t *Output);



uint8_t key_data_128[16] = {0x65, 0x32, 0x19, 0x8C, 0xC6, 0xE3, 0xF1, 0xF8, 0x7C, 0x3E, 0x1F, 0x0F, 0x87, 0x43, 0x21, 0x10};

uint8_t input_data_128[] = {0x8C, 0x46, 0xA3, 0xD1, 0xC1, 0x60, 0x30, 0x18, 0x16, 0x0B, 0x05, 0x82, 0x6E, 0xB7, 0x5B, 0x2D};
uint8_t cipher_data_128[] = {0xE5, 0x1E, 0x1B, 0x17, 0xC4, 0x4E, 0x5C, 0x14, 0x62, 0xBB, 0xFE, 0xC0, 0xDD, 0x60, 0xC0, 0xDC};

uint8_t key_data_192[] = {0xAD, 0xD6, 0x6B, 0xB5, 0x5A, 0x2D, 0x96, 0xCB, 0x65, 0x32, 0x19, 0x8C, 0xC6, 0xE3, 0xF1, 0xF8, 0x7C,
                          0x3E, 0x1F, 0x0F, 0x87, 0x43, 0x21, 0x10
                         };
uint8_t input_data_192[] = {0x16, 0x0B, 0x05, 0x82, 0x6E, 0xB7, 0x5B, 0x2D, 0xE7, 0x73, 0xB9, 0xDC, 0x73, 0x39, 0x9C, 0xCE};
uint8_t cipher_data_192[] = {0x3F, 0x37, 0xD1, 0x29, 0x7B, 0x8A, 0x34, 0x65, 0x61, 0x68, 0xA8, 0xD3, 0xDF, 0xBF, 0x18, 0x3A};

uint8_t key_data_256[] = {0x68, 0xB4, 0x5A, 0xAD, 0xD6, 0x6B, 0xB5, 0x5A, 0xAD, 0xD6, 0x6B, 0xB5, 0x5A, 0x2D, 0x96, 0xCB, 0x65,
                          0x32, 0x19, 0x8C, 0xC6, 0xE3, 0xF1, 0xF8, 0x7C, 0x3E, 0x1F, 0x0F, 0x87, 0x43, 0x21, 0x10
                         };
uint8_t input_data_256[] = {0xE7, 0x73, 0xB9, 0xDC, 0x73, 0x39, 0x9C, 0xCE, 0x3A, 0x9D, 0xCE, 0xE7, 0xA2, 0xD1, 0xE8, 0x74};
uint8_t cipher_data_256[] = {0xC7, 0x53, 0xE0, 0x9C, 0x9B, 0x1B, 0x29, 0xAD, 0x27, 0x2A, 0x68, 0x8D, 0xC9, 0x65, 0x39, 0x25};

uint8_t iv_data[16] = {0x68, 0xB4, 0x5A, 0xAD, 0xD6, 0x6B, 0xB5, 0x5A, 0xAD, 0xD6, 0x6B, 0xB5, 0x5A, 0x2D, 0x96, 0xCB};
uint8_t iv_data_192[16] = {0xC1, 0x60, 0x30, 0x18, 0x8C, 0x46, 0xA3, 0xD1, 0x68, 0xB4, 0x5A, 0xAD, 0xD6, 0x6B, 0xB5, 0x5A};
uint8_t iv_data_256[16] = {0x6E, 0xB7, 0x5B, 0x2D, 0x16, 0x0B, 0x05, 0x82, 0xC1, 0x60, 0x30, 0x18, 0x8C, 0x46, 0xA3, 0xD1};
uint8_t output_data[16] = {0};
void UartPortInit(UART_TypeDef* UARTx);

u8 temp_input_data_128[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t temp_key_data_128[16] = {0};
u8 temp_output_data_128[16] = {0x8C, 0x46, 0xA3, 0xD1, 0xC1, 0x60, 0x30, 0x18, 0x16, 0x0B, 0x05, 0x82, 0x6E, 0xB7, 0x5B, 0x2D};
u8 temp_output1_data_128[16] = {0x8C, 0x46, 0xA3, 0xD1, 0xC1, 0x60, 0x30, 0x18, 0x16, 0x0B, 0x05, 0x82, 0x6E, 0xB7, 0x5B, 0x2D};


int randongenerate16bytesData(u8 *p, u32 addr)
{
    u8 i, a;
    u16 hdata;
    for(i = 0; i < 16; i++)
    {
        hdata = i; //*((u16 *)(0x8000000+addr+i));
        a = hdata & 0xFF;
        *p = a;
        p++;
    }
    return 0;
}


int runpresstest(void)
{
    int i, ERROR = 0;
    randongenerate16bytesData(temp_key_data_128, 0x100);
    randongenerate16bytesData(temp_input_data_128, 0x200);
    ECB_128_encry(temp_key_data_128, temp_input_data_128, 0, temp_output_data_128);
    AES_ECB_Decrypt(temp_key_data_128, temp_output_data_128, 0, temp_output1_data_128);
    for(i = 0; i < 16; i++)
    {
        if(temp_output1_data_128[i] != temp_input_data_128[i])
        {
            ERROR++;
        }
    }

    return ERROR;
}

void PA15_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); //开启GPIOA,GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//开启复用时钟，这个一定要开
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//失能JTAG，使能SW

    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_15);
}


/********************************************************************************************************
**函数信息 ：int main (void)
**功能描述 ：开机后，ARMLED闪动
**输入参数 ：
**输出参数 ：
********************************************************************************************************/

int main(void)
{
    /* IF use AES, the SYSCLK must be set under 72MHz */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_AES, ENABLE);
    PA15_Init();
    while (1)
    {

        if(0 == runpresstest())
        {
            GPIO_SetBits(GPIOA, GPIO_Pin_15);
            GPIO_ResetBits(GPIOA, GPIO_Pin_15);
            GPIO_SetBits(GPIOA, GPIO_Pin_15);
        }
        else
        {
            GPIO_ResetBits(GPIOA, GPIO_Pin_15);
            GPIO_SetBits(GPIOA, GPIO_Pin_15);
            GPIO_ResetBits(GPIOA, GPIO_Pin_15);
            GPIO_SetBits(GPIOA, GPIO_Pin_15);
        }
    }
}

/********************************************************************************************************
**函数信息 ：void CBC_128_decry()
**功能描述 ：加密模式
**输入参数 ：
**输出参数 ：
**    备注 ：
********************************************************************************************************/
void ECB_128_encry(uint8_t *Key, uint8_t *Input, uint32_t Ilength, uint8_t *Output)
{
    AES_KeySize(CRL_AES128_KEY);
    AES_ECB_Encrypt( Key, Input, Ilength, Output);
}


/********************************************************************************************************
**函数信息 ：UartPortInit(UART_TypeDef* UARTx)
**功能描述 ：初始化串口
**输入参数 ：UART_TypeDef* UARTx ，选择UART1、UART2、UART3
**输出参数 ：无
********************************************************************************************************/
void UartPortInit(UART_TypeDef* UARTx)
{
    UART_InitTypeDef       UART_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;

    if(UARTx == UART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
    }
    else if(UARTx == UART2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
    }
    else if(UARTx == UART3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE);
    }

    UART_InitStructure.UART_BaudRate =  115200; //波特率115200
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;//数据位
    UART_InitStructure.UART_StopBits = UART_StopBits_1;//停止位
    UART_InitStructure.UART_Parity = UART_Parity_No ;
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;//输入输出模式
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
    UART_Init(UARTx, &UART_InitStructure);
    UART_Cmd(UARTx, ENABLE);  //UART 模块使能

    if(UARTx == UART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;   //uart1_tx  pa9
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;  //uart1_rx  pa10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure);

    }

    if(UARTx == UART2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;   //uart1_tx  pa2
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;  //uart1_rx  pa3
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure);

    }

    if(UARTx == UART3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;   //uart3_tx  pc10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;  //uart3_rx  pc11
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOC, &GPIO_InitStructure);

    }

}



/********************************************************************************************************
**函数信息 ：void UartSendByte(u8 dat)
**功能描述 ：UART发送数据
**输入参数 ：dat
**输出参数 ：
**    备注 ：
********************************************************************************************************/
void UartSendByte(u8 dat)
{
    UART_SendData(UART1, dat);
    while (!UART_GetFlagStatus(UART1, UART_FLAG_TXEPT));
}


/********************************************************************************************************
**函数信息 ：void UartSendGroup(u8* buf,u16 len)
**功能描述 ：UART发送数据
**输入参数 ：buf,len
**输出参数 ：
**    备注 ：
********************************************************************************************************/
void UartSendGroup(u8 *buf, u16 len)
{
    while (len--)
        UartSendByte(*buf++);
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