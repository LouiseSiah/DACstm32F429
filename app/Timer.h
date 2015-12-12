#ifndef __Timer_H__
#define __Timer_H__

#include <stdint.h>

typedef struct TIM6_t TIM6type;
struct TIM6_t
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t RESERVED1;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t RESERVED2;
  volatile uint32_t RESERVED3;
  volatile uint32_t RESERVED4;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
};

#define TIM6_reg ((TIM6type *)0x40001000)

enum OutputTriggerSource
{
  RESET_EGR_UG,
  ENABLE_CNT_EN,
  UPDATE_UEV
};

void getTim6AutoReloadValue(int value);
void getTim6PrescaleValue(int value);
void enableTim6Counter();
void enableTim6UpdateEvent();
void disableTim6UpdateEvent();
void enableUpdateRequestSource(int enable);
void selectionOfOutputTrigger(int outputTriggerSource);
void resetCounterBySetUG();
void onePulseMode();

#endif // __Timer_H__
