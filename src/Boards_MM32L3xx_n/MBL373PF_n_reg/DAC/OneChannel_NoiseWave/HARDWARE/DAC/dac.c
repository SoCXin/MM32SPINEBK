#include "dac.h"
#include "uart.h"

void Dac1_Init(void)
{

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;//使能GPIOA时钟
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;//使能DAC时钟
    GPIOA->CRL &= 0XFFF0FFFF;//PA4 anolog输入

    DAC->CR |= DAC_CR_TSEL1;//软件触发
    DAC->CR |= DAC_CR_WAVE1_0;//噪声波生成
    DAC->CR |= DAC_CR_MAMP1_3;//噪声生成模式下选择屏蔽位
    DAC->CR |= 1 << 2;
    DAC->CR &= (~DAC_CR_BOFF1);//DAC通道1输出缓存使能
    DAC->CR |= DAC_CR_EN1; //DAC1通道使能
    DAC->DHR12L1 = 0x7FF0;

}


