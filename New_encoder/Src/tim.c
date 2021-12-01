#include "tim.h"
#include "global.h"

extern float VELOSITY;

void TIM6_DAC_IRQHandler()
{
	TIM6->SR &= ~TIM_SR_UIF;
	VELOSITY = 0;
	dt=0.1;
	flag = CalculateMode;
}

void TIM6_init() //отсчитывает  секунды для определения 0.1 скорости
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // Включение тактирования таймера
	TIM6->CR1 |= TIM_CR1_ARPE; // autoreload enable
	TIM6->ARR = 400-1;
	TIM6->PSC = 2000-1;
	TIM6->DIER |= TIM_DIER_UIE; // Включение прерывания таймера
	NVIC_SetPriority(TIM6_DAC_IRQn,3); // Установка приоритета прерывания
	NVIC_EnableIRQ(TIM6_DAC_IRQn); // Включение прерывания
	TIM6->CR1 |= TIM_CR1_CEN; //Включение таймера
}

void PWM_Init_PC8(){
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->ARR = 40000-1;
    TIM3->PSC = 0;
    TIM3->CCMR2 |= TIM_CCMR2_OC3M;
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE;
    TIM3->CCER |= TIM_CCER_CC3P;
    TIM3->CCER |= TIM_CCER_CC3E; //включение канала
    TIM3->CR1 |= TIM_CR1_CEN; //включение
}
