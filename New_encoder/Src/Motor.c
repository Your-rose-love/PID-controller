#include "global.h"
#include "Motor.h"

void Motor_init(){
	PWM_Init_PC8();
	GPIOPC8_init();
}
