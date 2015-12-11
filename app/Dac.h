#ifndef __Dac_H__
#define __Dac_H__

#include <stdint.h>

typedef struct DAC_t DACtype;
struct DAC_t
{
  volatile uint32_t DAC_CR;
  volatile uint32_t DAC_SWTRIGR;
  volatile uint32_t DAC_DHR12R1;
  volatile uint32_t DAC_DHR12L1;
  volatile uint32_t DAC_DHR8R1;
  volatile uint32_t DAC_DHR12R2;
  volatile uint32_t DAC_DHR12L2;
  volatile uint32_t DAC_DHR8R2;
  volatile uint32_t DAC_DHR12RD;
  volatile uint32_t DAC_DHR12LD;
  volatile uint32_t DAC_DHR8RD;
  volatile uint32_t DAC_DOR1;
  volatile uint32_t DAC_DOR2;
  volatile uint32_t DAC_SR;
};

#define Dac_reg ((DACtype*)0x40007400)
#define YES 1
#define NO  0

#define WAVE_GENERATION_DISABLE 0
#define NOISE_WAVE              1
#define TRIANGLE_WAVE           2

enum TriggerSource
{
	TIMER6,
	TIMER8,
	TIMER7,
	TIMER5,
	TIMER2,
	TIMER4,
	EXTERNAL_TRIGGER,
	SW_TRIGGER
};

enum TriangleAmplitude
{
  AMPLITUDE_1,
  AMPLITUDE_3,
  AMPLITUDE_7,
  AMPLITUDE_15,
  AMPLITUDE_31,
  AMPLITUDE_63,
  AMPLITUDE_127,
  AMPLITUDE_255,
  AMPLITUDE_511,
  AMPLITUDE_1023,
  AMPLITUDE_2047,
  AMPLITUDE_4095
};

enum UnmaskBits
{
  BITS_0,
  BITS_0TO1,
  BITS_0TO2,
  BITS_0TO3,
  BITS_0TO4,
  BITS_0TO5,
  BITS_0TO6,
  BITS_0TO7,
  BITS_0TO8,
  BITS_0TO9,
  BITS_0TO10,
  BITS_0TO11
};

void enableDAC1(int enable);
void enableDAC2(int enable);
void setDAC1buffer(int enable);
void setDAC2buffer(int enable);
void enableDAC1TriggerAndSelect(int enable, int triggerSource);
void enableDAC2TriggerAndSelect(int enable, int triggerSource);
void selectDAC1WaveType(int waveType, int amplitudeOrMask);
void selectDAC2WaveType(int waveType, int amplitudeOrMask);
void sendSWTriggerToDac1();
void sendSWTriggerToDac2();

#endif // __Dac_H__
