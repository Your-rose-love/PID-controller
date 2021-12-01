#include "global.h"
#include "Encoder.h"

void Encoder_init(){
	GPIOEncoder_init();
	TIM6_init();
	SET_DELAY_ZEROS();
}
