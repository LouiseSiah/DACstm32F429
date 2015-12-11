#include "Timer.h"

/**
 * brief  @ This function is to get the value to load into Auto-Reload Register(ARR).
 *        @ Maximum value for ARR is 0xFFFF or in decimal 65,536.
 *
 * param  @ value - The value that user want to put in ARR.
 *
 * retval @ none
 *
 */
void getTim6AutoReloadValue(int value)
{
  if(value > 0xFFFF)
      TIM6_reg->ARR = 0xFFFF;
    
  TIM6_reg->ARR = value ;
}

/**
 * brief  @ This function is to get the value to load into Prescaler (PSC).
 *        @ The counter clock frequency CK_CNT = fCK_PSC/ (PSC[15:0] + 1).
 *        @ Maximum value for PSC is 0xFFFF or in decimal 65,536.
 *
 * param  @ value - The value that user want to put in PSC.
 *
 * retval @ none
 *
 */
void getTim6PrescaleValue(int value)
{
  if(value > 0xFFFF)
      TIM6_reg->PSC = 0xFFFF;
    
  TIM6_reg->PSC = value ;
}

/**
 * brief  @ To run/enable the timer 6 counter.
 *
 * param  @ none
 *
 * retval @ none
 *
 */
void enableTim6Counter()
{
  TIM6_reg->CR1 |= 1;
}

/*
 * brief  @ To enable the Update Event(UEV) of timer 6.
 *		  @ Once UEV happen , counter will be re-initialized.
 * param  @ none
 * retval @ none
 *
 */
void enableTim6UpdateEvent()
{
  TIM6_reg->CR1 &= ~ (1 << 1);
}

/**
 * brief  @ To disable the Update Event(UEV) of timer 6.
 * param  @ none
 * retval @ none
 *
 */
void disableTim6UpdateEvent()
{
  TIM6_reg->CR1 |= (1 << 1);
}


/**
 * brief  @ To select the UEV event sources to Only counter overflow/underflow
 * 			generates an update interrupt or DMA request if enabled.
 * param  @ enable - To enable or disable URS.
 * retval @ none
 *
 */
void enableUpdateRequestSource(int enable)
{
  if(enable)
    TIM6_reg->CR1 |= (1 << 2);
  else
    TIM6_reg->CR1 &= ~ (1 << 2);
}

/**
 * brief  @ To select output Trigger sources.
 * param  @ outputTriggerSource - Indicate which source had been chosen.
 * retval @ none
 *
 */
void selectionOfOutputTrigger(int outputTriggerSource)
{
  TIM6_reg->CR2 &= ~ (7 << 4);
  TIM6_reg->CR2 |= (outputTriggerSource << 4);
}
