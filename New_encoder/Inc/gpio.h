#ifndef _GPIO_H_
#define _GPIO_H_

#include "global.h"

void GPIOEncoder_init();
void GPIOAPWM_init ();
void GPIOPC8_init();
void PWM_SET_VAL(int);
void GPIOButton_init();

#endif
