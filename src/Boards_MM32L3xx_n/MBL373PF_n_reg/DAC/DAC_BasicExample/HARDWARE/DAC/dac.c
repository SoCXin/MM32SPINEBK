#include "dac.h"
#include "uart.h"

void Dac1_Init(void)
{

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //使能GPIOA时钟
    RCC->APB1ENR |= RCC_APB1ENR_DACEN; //使能DAC时钟
    GPIOA->CRL &= 0XFFF0FFFF; //PA4 anolog输入
    DAC->CR |= DAC_CR_BOFF1; //DAC1输出缓存关闭 BOFF1=1
    DAC->CR |= DAC_CR_EN1; //DAC1通道使能
    DAC->DHR12R1 = ~DAC_DHR12R1_DACC1DHR;

}

//设置通道1输出电压
void Dac1_Set_Vol(u16 vol)
{
    float temp = vol;
    temp /= 1000;
    temp = temp * 4096 / 3.3;
    DAC->DHR12R1 = temp;

}

