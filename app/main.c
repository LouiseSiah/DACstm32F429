#include "stm32f4xx.h"
// #include "RNG.h"
#include "stm32f4xx_hal.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Dac.h"
#include "Dma.h"
#include "Timer.h"
#include <math.h>
#include <stdint.h>

#define	radian_per_degree	0.0174532925
int count = 0;
void DAC_setup()
{
	dacUnresetEnableClock();
//	selectDAC1WaveType(WAVE_GENERATION_DISABLE, NO);
//	selectDAC1WaveType(TRIANGLE_WAVE, AMPLITUDE_255);
	selectDAC1WaveType(NOISE_WAVE,  BITS_0TO8);
//	selectDAC2WaveType(WAVE_GENERATION_DISABLE, NO);
//	selectDAC2WaveType(NOISE_WAVE,  BITS_0TO8);
	selectDAC2WaveType(TRIANGLE_WAVE, AMPLITUDE_511);
	setDAC1buffer(YES);
	setDAC2buffer(YES);
	enableDAC1TriggerAndSelect(YES, TIMER6);
//   enableDAC1TriggerAndSelect(YES, SW_TRIGGER);
//	enableDAC1TriggerAndSelect(NO, NO);
	enableDAC2TriggerAndSelect(YES, TIMER6);
//	enableDAC2TriggerAndSelect(NO, NO);
	enableDAC1DMA(NO);
	enableDAC2DMA(NO);
	enableDAC1(YES);
	enableDAC2(YES);
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
  getTim6AutoReloadValue(0x1);
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
void dma_setup()
{
	dma1UnresetEnableClock();
	configureDMA1ForDAC1();
	cleaDmaHighInterruptFlag(CLEAR_S5);
	enableMemoryIncrement(YES);
	enablePeripheralIncrement(NO);
	memoryDataSize(HALF_WORD);
	peripheralDataSize(HALF_WORD);
	dataTransferDirection(MemoryToPeripheral);
	priority(VeryHigh);
	enableMemoryCircularMode(NO);
	enableDoubleBufferMode(YES);
	disableDma();
}

void usingTimerTriggerHalfTri()
{
	GPIO_setup();
	DAC_setup();
	TIMER6_setup();
	int temp1;
	int small[360];
	int temp2;
	unsigned int degree = 0;

	enableTim6Counter();

	for(degree = 0; degree < 360; degree++)
	{
		temp2 = (2047 * cos(radian_per_degree * degree));
		temp2 = (2048 - temp2);
		small[degree] = (temp2 / 2);
		temp1 += 10;
		Dac_reg->DAC_DHR12R2 = small[degree];
		Dac_reg->DAC_DHR12R1 = temp1;

	}

	//USING TIMER TRIGGER
	/*enableTim6Counter();
	temp2 = 1000;
	Dac_reg->DAC_DHR12R1 = temp2;

	while(1)
	{
//			delay(100);
//			sendSWTriggerToDac1();
	}
	*/

}

void cosWaveNoTrigger()
{
  GPIO_setup();
  DAC_setup();

  int temp1 = 0;
  unsigned int degree = 0;
	for(degree = 0; degree < 360; degree++)
	{

//		temp1 = (2047 * cos(radian_per_degree * degree));
//		temp1 = (2048 - temp1);

		temp1 += 10;

		Dac_reg->DAC_DHR12R1 = temp1;
		Dac_reg->DAC_DHR8R2 = temp1;

//		Dac_reg->DAC_DHR12R1 = temp2;
		delay(1);
//		sendSWTriggerToDac1();

	}
}

void DMA1_Stream5_IRQHandler(void)
{
	int read;
	read = Dma1_reg->HISR;
	//Dma1_reg->HIFCR
/* not working
	if(count % 2 == 0)
	{
		memory0BaseAddr((uint32_t)sinWave);
		memory1BaseAddr((uint32_t)cosWave);
	}
	else
	{
	 	memory0BaseAddr((uint32_t)cosWave);
	 	memory1BaseAddr((uint32_t)triWave);
	}

	Dma1_reg->HIFCR &= 0x440;
*/
}
void usingDMAandTimerTrigger()
{
	GPIO_setup();
	DAC_setup();
	TIMER6_setup();
	short int cosWave[360];
	short int sinWave[360];
	short int triWave[360];
	int degree;

 	/* forDMA */
 	for(degree = 0; degree < 360; degree++)
 	{
 		cosWave[degree] = (2047 * cos(radian_per_degree * degree));
 		cosWave[degree] = (2048 - cosWave[degree]);
 		sinWave[degree] = (2047 * sin(radian_per_degree * degree));
 		sinWave[degree] = (2048 - sinWave[degree]);

 		if(degree < 180)
 			triWave[degree] = (degree + 20) * 10 ;
 		else
 		{
 			triWave[degree] = triWave[degree-180];
 			triWave[degree] = 2000 - triWave[degree];
 		}

 	}

 	dma_setup();
 	numberOfDataTransferDMA(degree);
 	peripheralBaseAddr((uint32_t)&(Dac_reg->DAC_DHR12R1));
 	memory0BaseAddr((uint32_t)cosWave);
 	memory1BaseAddr((uint32_t)triWave);
// 	int readDma = 0;
// 	readDma = Dma1_reg->S5.CR;

// 	readDma = 0;
// 	readDma = Dac_reg->DAC_CR;
 	enableTim6Counter();
 	enableDma();
 }

/*
 * code for DAC
 */
int main(void)
{

//  int APBclock, sysClock;
//  sysClock = getSystemClock();
//  APBclock = getAPB1Clock(sysClock);
//	int sample;

//	usingDMAandTimerTrigger();
//	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

	while(1)
	{


		usingTimerTriggerHalfTri();

//		cosWaveNoTrigger();


	}
}
