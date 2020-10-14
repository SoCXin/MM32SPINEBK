#include "dac.h"
#include "uart.h"
void TIM2_Trig_DAC_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;//
    TIM2->ARR |= 0x000F;//Period
    TIM2->PSC |= 0x000F;//Prescale
    TIM2->CR1 &= 0xFCFF;//ClockDivision
    TIM2->CR1 &= 0xFFEF;//CounterMode_Up

    TIM2->CR2 |= TIM_CR2_MMS_1;//TIM2 TRGO Selection
}
void Dac1_Init(void)
{

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;//使能GPIOA时钟
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;//使能DAC时钟
    GPIOA->CRL &= 0XFFF0FFFF;//PA4 anolog输入

    DAC->CR |= DAC_CR_TSEL1_2;//TIM2 TRIGO
    DAC->CR |= DAC_CR_WAVE1_1;//DAC_WaveGeneration_Triangle
    DAC->CR |= 0x0A00;//DAC_TriangleAmplitude_2047
    DAC->CR |= 1 << 2;
    DAC->CR |= DAC_CR_BOFF1;//DAC_OutputBuffer_Disable

    //DAC->CR|=DAC_CR_EN1;//DAC通道1使能

}
void Dac2_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;//使能GPIOA时钟
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;//使能DAC时钟
    GPIOA->CRL &= 0XFF0FFFFF;//PA5 anolog输入

    DAC->CR |= ( DAC_CR_TSEL1_2 << 16 );//TIM2 TRIGO
    DAC->CR |= ( DAC_CR_WAVE1_1 << 16 );//DAC_WaveGeneration_Triangle
    DAC->CR |= ( 0x0900 << 16 );//DAC_TriangleAmplitude_1023
    DAC->CR |= ( 1 << ( 2 + 16 ) );
    DAC->CR |= ( DAC_CR_BOFF1 << 16 );//DAC_OutputBuffer_Disable

    //DAC->CR|=( DAC_CR_EN1 << 16 );//DAC通道2使能
}

