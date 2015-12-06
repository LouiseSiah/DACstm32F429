#include "Dac.h"

/**
 * brief  @ This function is to enable or disable DAC channel1.
 *
 * param  @ enable - To indicate enable of disable.
 *
 * retval @ none
 *
 */
void enableDAC1(int enable)
{
  if(enable)
    Dac_reg->DAC_CR |= 1; 
  else
    Dac_reg->DAC_CR &= ~1; 
}

/**
 * brief  @ This function is to enable or disable DAC channel2.
 *
 * param  @ enable - To indicate enable of disable.
 *
 * retval @ none
 *
 */
void enableDAC2(int enable)
{
  if(enable)
    Dac_reg->DAC_CR |= (1 << 16); 
  else
    Dac_reg->DAC_CR &= ~(1 << 16); 
}

/**
 * brief  @ This function is to enable or disable the DAC output buffer1.
 *
 * param  @ enable - To indicate enable of disable.
 *
 * retval @ none
 *
 */
void setDAC1buffer(int enable)
{
  if(enable)
	  Dac_reg->DAC_CR &= ~(1 << 1);
  else
	  Dac_reg->DAC_CR |= (1 << 1);

}

/**
 * brief  @ This function is to enable or disable the DAC output buffer2.
 *
 * param  @ enable - To indicate enable of disable.
 *
 * retval @ none
 *
 */
void setDAC2buffer(int enable)
{
  if(enable)
	  Dac_reg->DAC_CR &= ~(1 << 17);
  else
	  Dac_reg->DAC_CR |= (1 << 17);
}

/**
 * brief  @ This function is to enable or disable the DAC1 trigger.
 * brief  @ This function is used to select the trigger source also if there is enable trigger.
 *
 * param  @ enable - To indicate enable of disable.
 *
 * retval @ none
 *
 */
void enableDAC1TriggerAndSelect(int enable, int triggerSource)
{
  if(enable)
  {
	  Dac_reg->DAC_CR |= (1 << 2);
    Dac_reg->DAC_CR &= ~(7 << 3);
    Dac_reg->DAC_CR |= (triggerSource << 3);
  }
  else
	  Dac_reg->DAC_CR &= ~(1 << 2);
}

/**
 * brief  @ This function is to enable or disable the DAC2 trigger.
 * brief  @ This function is used to select the trigger source also if there is enable trigger.
 *
 * param  @ enable - To indicate enable of disable.
 *
 * retval @ none
 *
 */
void enableDAC2TriggerAndSelect(int enable, int triggerSource)
{
  if(enable)
  {
	  Dac_reg->DAC_CR |= (1 << 18);
    Dac_reg->DAC_CR &= ~(7 << 19);
    Dac_reg->DAC_CR |= (triggerSource << 19);
  }
  else
	  Dac_reg->DAC_CR &= ~(1 << 18);
}
