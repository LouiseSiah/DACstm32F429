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

void DAC_setup()
{
	dacUnresetEnableClock();
	selectDAC1WaveType(WAVE_GENERATION_DISABLE, NO);
//  selectDAC1WaveType(TRIANGLE_WAVE, AMPLITUDE_2047);
//  selectDAC1WaveType(WAVE_GENERATION_DISABLE, NO);
	selectDAC2WaveType(WAVE_GENERATION_DISABLE, NO);
	setDAC1buffer(YES);
	setDAC2buffer(NO);
	enableDAC1TriggerAndSelect(YES, TIMER6);
//   enableDAC1TriggerAndSelect(YES, SW_TRIGGER);
//	enableDAC1TriggerAndSelect(NO, NO);
	enableDAC2TriggerAndSelect(NO, NO);
	enableDAC1DMA(YES);
//	enableDAC2DMA(NO);
	enableDAC1(YES);
	enableDAC2(NO);
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
	enableMemoryCircularMode(YES);
	enableDoubleBufferMode(NO);
	disableDma();
}

void usingTimerTriggerHalfTri()
{
	GPIO_setup();
	DAC_setup();
	TIMER6_setup();
	int temp1;

	enableTim6Counter();

	for(temp1 = 0; temp1 < 4000; temp1 += 10)
	{
		Dac_reg->DAC_DHR12R1 = temp1;
		sendSWTriggerToDac1();
		delay(100);

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

void sinWaveNoTrigger()
{
  GPIO_setup();
  DAC_setup();

  int temp2;
  unsigned int degree = 0;
	for(degree = 0; degree < 360; degree++)
	{

		temp2 = (2047 * cos(radian_per_degree * degree));
		temp2 = (2048 - temp2);
		Dac_reg->DAC_DHR12R1 = temp2;
//		temp2 += 10;
//		Dac_reg->DAC_DHR12R1 = temp2;
		delay(1);
//		sendSWTriggerToDac1();

	}
}

void usingDMAandTimerTrigger()
{
	GPIO_setup();
	DAC_setup();
	TIMER6_setup();
	short int temp1[360];
	int degree;

 	/* forDMA */
 	 for(degree = 0; degree < 360; degree++)
 	 {
 		 temp1[degree] = (2047 * cos(radian_per_degree * degree));
 		 temp1[degree] = (2048 - temp1[degree]);
// 		 temp1[degree] += 10;
 	 }

 	 dma_setup();
 	 numberOfDataTransferDMA(degree);
 	 peripheralBaseAddr((uint32_t)&(Dac_reg->DAC_DHR12R1));
 	 memory0BaseAddr((uint32_t)temp1);
// 	 memory1BaseAddr((uint32_t)temp1);
 	 int readDma = 0;
 	 readDma = Dma1_reg->S5.CR;

 	 readDma = 0;
 	 readDma = Dac_reg->DAC_CR;
 	 enableTim6Counter();
 	 enableDma();
 	 degree = Dac_reg->DAC_DHR12R1;
}

/*
 * code for DAC
 */
int main(void)
{

//  int APBclock, sysClock;
//  sysClock = getSystemClock();
//  APBclock = getAPB1Clock(sysClock);
	int sample;

	usingDMAandTimerTrigger();

	while(1)
	{

		sample = Dac_reg->DAC_DHR12R1;

		sample = Dma1_reg->HISR & (0xF << 8);


//		usingTimerTriggerHalfTri();

//		sinWaveNoTrigger();


	}
}
