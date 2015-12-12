#include "stm32f4xx.h"
// #include "RNG.h"
#include "stm32f4xx_hal.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Dac.h"
#include "Timer.h"
#include <math.h>
#include <stdint.h>

#define	radian_per_degree	0.0174532925

void DAC_setup()
{
  dacUnresetEnableClock();
//  selectDAC1WaveType(TRIANGLE_WAVE, AMPLITUDE_255);
  selectDAC1WaveType(WAVE_GENERATION_DISABLE, NO);
  selectDAC2WaveType(WAVE_GENERATION_DISABLE, NO);
  enableDAC1(YES);
  enableDAC2(NO);
  setDAC1buffer(YES);
  setDAC2buffer(NO);
    enableDAC1TriggerAndSelect(YES, TIMER6);
//    enableDAC1TriggerAndSelect(YES, SW_TRIGGER);
  //  enableDAC1TriggerAndSelect(NO, NO);
    enableDAC2TriggerAndSelect(NO, NO);
}

void GPIO_setup()
{
  configureAnalog(4, PORTA);
  configureAnalog(5, PORTA);
  configureOutput(GPIO_V_HIGH_SPEED, 4, PORTA);
  configureOutput(GPIO_V_HIGH_SPEED, 5, PORTA);
}

void TIMER6_setup()
{
  timer6UnresetEnableClock();
  getTim6AutoReloadValue(1);
  getTim6PrescaleValue(0);
//  onePulseMode();
//  disableTim6UpdateEvent();
  selectionOfOutputTrigger(UPDATE_UEV);
//  enableTim6Counter();
}

void delay(uint32_t delayCount)
{
	while(delayCount != 0)
		delayCount--;
}

//=====test code for TIMER=====
/*int main(void)
{
  int sample = 0;
  TIMER6_setup();

  enableTim6Counter();

  while(1)
  {
	 if(TIM6_reg->SR & 1)
//	 if(TIM6_reg->CNT == TIM6_reg->ARR)
     {
       sample = TIM6_reg->CNT;
       TIM6_reg->SR &= ~ (1); //clear overflow
//       resetCounterBySetUG();
       enableTim6Counter();
       sample = TIM6_reg->CNT;
     }
     else
       sample = TIM6_reg->CNT;
  }
}*/


/*
 * code for DAC
 */
int main(void)
{
  GPIO_setup();
  DAC_setup();
  TIMER6_setup();
  int temp1;
  int sample = 0;
//  int temp2;
//  int APBclock, sysClock;
  unsigned int degree = 0;
//  sysClock = getSystemClock();
//  APBclock = getAPB1Clock(sysClock);
  enableTim6Counter();

	while(1)
	{

		temp1 = 0;
//		temp2 = 0;

		for(degree = 0; degree < 360; degree++)
		{
//			sample = TIM6_reg->CNT;
//			temp1 = (2047 * cos(radian_per_degree * degree));
//			temp1 = (2048 - temp1);
//			Dac_reg->DAC_DHR12R1 = temp1;
			temp1 += 10;
			Dac_reg->DAC_DHR12R1 = temp1;
//			temp2 = (2047 * sin(radian_per_degree * degree));
//			temp2 = (2048 - temp2);
//			Dac_reg->DAC_DHR12R2 = temp2;
//			delay(1);
//			sendSWTriggerToDac1();
			while(1)
			{
//
		      if(TIM6_reg->SR & 1)
		      {
		    	TIM6_reg->SR &= ~ (1);
//				enableTim6Counter();
//		    	sendSWTriggerToDac1();
				break;
		      }
//		      sample = TIM6_reg->CNT;
//
			}

		}

	}
}
