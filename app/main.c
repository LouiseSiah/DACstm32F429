#include "stm32f4xx.h"
// #include "RNG.h"
#include "stm32f4xx_hal.h"
//#include "Gpio.h"
#include "Rcc.h"
#include <stdint.h>

int main(void)
{
	int datax;
	// int pass = RNG_reg->RNG_SR;
	// enableRNG();

//	configurePin(GPIO_MODE_OUTPUT, PIN_13, PORTG);

	while(1)
	{
//		pass = readyToRead();
		// if(pass)
			datax = 05;
//		pass = 1;

		// datax = RNG_reg->RNG_DR;
	}
}

