#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#define CalculateMode 1
#define StopMode 0
#define DELAY	100

#include "stm32f0xx.h"
#include "gpio.h"
#include "tim.h"

float VELOSITY_UST[7];
float SET_VELOSITY;
float VELOSITY;
float VELOSITY_DELAY[DELAY];
float dt_DELAY[DELAY];
float dt;
int PWM;
uint8_t flag;

#endif
