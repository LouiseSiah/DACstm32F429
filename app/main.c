#include "stm32f4xx.h"
// #include "RNG.h"
#include "stm32f4xx_hal.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Dac.h"
#include <stdint.h>

void GPIO_setup();
void DAC_setup();

void delay(uint32_t delayCount)
{
	while(delayCount != 0)
		delayCount--;
}

int main(void)
{
  unsigned int temp1 = 0;
  unsigned int degree = 0;

	while(1)
	{
		for(degree = 0; degree < 360; degree++)
		{
			temp1 += 11;
			Dac_reg->DAC_DHR12R1 = temp1;
			delay(100);
		}
	}
}

void GPIO_setup()
{
  configureAnalog(4, PORTA);
  configureOutput(GPIO_V_HIGH_SPEED, 4, PORTA);
}

void DAC_setup()
{
  enableDAC1(YES);
  enableDAC2(NO);
  setDAC1buffer(YES);
  setDAC2buffer(NO);
}

