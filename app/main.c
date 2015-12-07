#include "stm32f4xx.h"
// #include "RNG.h"
#include "stm32f4xx_hal.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Dac.h"
#include <math.h>
#include <stdint.h>

#define	radian_per_degree	0.0174532925

void DAC_setup()
{
  dacUnresetEnableClock();
  enableDAC1(YES);
  enableDAC2(NO);
  setDAC1buffer(YES);
  setDAC2buffer(NO);
  enableDAC1TriggerAndSelect(YES, SW_TRIGGER);
  enableDAC2TriggerAndSelect(NO, NO);
  selectDAC1WaveType(TRIANGLE_WAVE, AMPLITUDE_4095);
//  selectDAC1WaveType(WAVE_GENERATION_DISABLE, NO);
  selectDAC2WaveType(WAVE_GENERATION_DISABLE, NO);
}

void GPIO_setup()
{
  configureAnalog(4, PORTA);
  configureAnalog(5, PORTA);
  configureOutput(GPIO_V_HIGH_SPEED, 4, PORTA);
  configureOutput(GPIO_V_HIGH_SPEED, 5, PORTA);
}

void delay(uint32_t delayCount)
{
	while(delayCount != 0)
		delayCount--;
}

int main(void)
{
  GPIO_setup();
  DAC_setup();
  int temp1;
  int temp2;
  unsigned int degree = 0;

	while(1)
	{
		temp1 = 0;
//		temp2 = 0;

		for(degree = 0; degree < 360; degree++)
		{
//			temp1 = (2047 * cos(radian_per_degree * degree));
//			temp1 = (2048 - temp1);
//			Dac_reg->DAC_DHR12R1 = temp1;
//			temp1 += 11;
			Dac_reg->DAC_DHR12R1 = 0;
//			temp2 = (2047 * sin(radian_per_degree * degree));
//			temp2 = (2048 - temp2);
//			Dac_reg->DAC_DHR12R2 = temp2;
			delay(10);
			sendSWTriggerToDac1();
		}

	}
}

