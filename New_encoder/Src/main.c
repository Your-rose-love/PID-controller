#include "global.h"
#include "main.h"

int main(void)
{

	Encoder_init();
	Motor_init();
	Button_init();

	while(1)
	{
		PID_ENABLE();
	}
}
