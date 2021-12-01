#include "gpio.h"
#include "global.h"

void EXTI0_1_IRQHandler()
{
	EXTI->PR |= EXTI_PR_PIF0;
	EXTI->PR |= EXTI_PR_PR0; // Снятие флага прерывания
	static int timer=0;
	static uint8_t counter=0;
	timer += TIM6->CNT;
	TIM6->CNT = 0;
	counter++;
	if (counter==100){
		if (DELAY==0){
			VELOSITY=300/(timer*0.00025); //60c*5оборотов/(timer*1/(8meg/PSC))
			dt=timer*0.00025;
		}
		else if(DELAY>0){
			VELOSITY=VELOSITY_DELAY[0];
			dt=dt_DELAY[0];
			for (int i=0; i<DELAY-1;i++){
				VELOSITY_DELAY[i]=VELOSITY_DELAY[i+1];
				dt_DELAY[i]=dt_DELAY[i+1];
			}
			VELOSITY_DELAY[DELAY-1]=300/(timer*0.00025); // Количество оборотов в минуту
			dt_DELAY[DELAY-1]=timer*0.00025;
		}
		counter=0;
		timer=0;
		flag = CalculateMode;
	}
}

void GPIOEncoder_init()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включение тактирования
	GPIOA->MODER &= ~GPIO_MODER_MODER1; // PA0-input mode
	EXTI->IMR |= EXTI_IMR_IM0; // Запрос прерывания не маскируется
	EXTI->EMR |= EXTI_EMR_EM0; // Запрос события не маскируется
	EXTI->RTSR |= EXTI_RTSR_RT0; // Rising trigger enabled
	SYSCFG->EXTICR[1] &= ~0xF; // Выбор источника внешнего прерывания
	NVIC_SetPriority(EXTI0_1_IRQn,9); // Установка приоритета прерывания
	NVIC_EnableIRQ(EXTI0_1_IRQn); // Включение прерывания
}

void EXTI2_3_IRQHandler()
{
	EXTI->PR |= EXTI_PR_PIF1;
	EXTI->PR |= EXTI_PR_PR1;
	static uint8_t button=0;
	button++;
	SET_VELOSITY=VELOSITY_UST[button];
	if(button==7){
		button=0;
		SET_VELOSITY=VELOSITY_UST[button];
	}

}

void GPIOButton_init()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включение тактирования
	GPIOA->MODER &= ~GPIO_MODER_MODER2; // PA0-input mode
	EXTI->IMR |= EXTI_IMR_IM2; // Запрос прерывания не маскируется
	EXTI->EMR |= EXTI_EMR_EM2; // Запрос события не маскируется
	EXTI->RTSR |= EXTI_RTSR_RT2; // Rising trigger enabled
	SYSCFG->EXTICR[1] &= ~0xF; // Выбор источника внешнего прерывания
	NVIC_SetPriority(EXTI2_3_IRQn,8); // Установка приоритета прерывания
	NVIC_EnableIRQ(EXTI2_3_IRQn); // Включение прерывания
}

void GPIOPC8_init(){
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= GPIO_MODER_MODER8_1; //AF
}


void PWM_SET_VAL( int PWM_val){
  	TIM3->CCR3 = PWM_val; // от 0 до 40000
}

