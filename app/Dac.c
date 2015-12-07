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
    Dac_reg->DAC_CR &= ~ 1; 
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
    Dac_reg->DAC_CR &= ~ (1 << 16); 
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
	  Dac_reg->DAC_CR &= ~ (1 << 1);
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
	  Dac_reg->DAC_CR &= ~ (1 << 17);
  else
	  Dac_reg->DAC_CR |= (1 << 17);
}

/**
 * brief  @ This function is to enable or disable the DAC1 trigger.
 * brief  @ This function is used to select the trigger source also if there is enable trigger.
 *
 * param  @ enable        - To indicate enable of disable.
 * param  @ triggerSource - The source was chose to trigger.
 *
 * retval @ none
 *
 */
void enableDAC1TriggerAndSelect(int enable, int triggerSource)
{
  if(enable)
  {
	Dac_reg->DAC_CR |= (1 << 2);
    Dac_reg->DAC_CR &= ~ (7 << 3);
    Dac_reg->DAC_CR |= (triggerSource << 3);
  }
  else
	Dac_reg->DAC_CR &= ~ (1 << 2);
}

/**
 * brief  @ This function is to enable or disable the DAC2 trigger.
 * brief  @ This function is used to select the trigger source also if there is enable trigger.
 *
 * param  @ enable - To indicate enable of disable.
 * param  @ triggerSource - The source was chose to trigger.
 *
 * retval @ none
 *
 */
void enableDAC2TriggerAndSelect(int enable, int triggerSource)
{
  if(enable)
  {
	Dac_reg->DAC_CR |= (1 << 18);
    Dac_reg->DAC_CR &= ~ (7 << 19);
    Dac_reg->DAC_CR |= (triggerSource << 19);
  }
  else
	Dac_reg->DAC_CR &= ~(1 << 18);
}

/**
 * brief  @ This function is to select the type of wave generated of DAC1.
 * brief  @ This function is used to select the amplitude of triangle wave 
 *          or the unmask bits of LSFR (noise wave).
 *
 * param  @ waveType        - To indicate which waveform had been chosen.
 * param  @ amplitudeOrMask - The amplitude of triangle wave or the unmask bits of LSFR (noise wave)
 *                            that had been chosen by user.
 *
 * retval @ none
 *
 */
void selectDAC1WaveType(int waveType, int amplitudeOrMask)
{
  if(!waveType) // WAVE_GENERATION_DISABLE
  {
    Dac_reg->DAC_CR &= ~ (3 << 6);
    Dac_reg->DAC_CR |= (waveType << 6);
  }
  else if(waveType == NOISE_WAVE)
  {
    Dac_reg->DAC_CR &= ~ (3 << 6);
    Dac_reg->DAC_CR |= (waveType << 6);
    Dac_reg->DAC_CR &= ~ (0xF << 8);
    Dac_reg->DAC_CR |= (amplitudeOrMask << 8);
  }
  else if(waveType == TRIANGLE_WAVE)
  {
    Dac_reg->DAC_CR &= ~ (3 << 6);
    Dac_reg->DAC_CR |= (waveType << 6);
    Dac_reg->DAC_CR &= ~ (0xF << 8);
    Dac_reg->DAC_CR |= (amplitudeOrMask << 8);
  }
}

/**
 * brief  @ This function is to select the type of wave generated of DAC2.
 * brief  @ This function is used to select the amplitude of triangle wave 
 *          or the unmask bits of LSFR (noise wave).
 *
 * param  @ waveType        - To indicate which waveform had been chosen.
 * param  @ amplitudeOrMask - The amplitude of triangle wave or the unmask bits of LSFR (noise wave)
 *                            that had been chosen by user.
 *
 * retval @ none
 *
 */
void selectDAC2WaveType(int waveType, int amplitudeOrMask)
{
  if(!waveType) // WAVE_GENERATION_DISABLE
  {
    Dac_reg->DAC_CR &= ~ (3 << 22);
    Dac_reg->DAC_CR |= (waveType << 22);
  }
  else if(waveType == NOISE_WAVE)
  {
    Dac_reg->DAC_CR &= ~ (3 << 22);
    Dac_reg->DAC_CR |= (waveType << 22);
    Dac_reg->DAC_CR &= ~ (0xF << 24);
    Dac_reg->DAC_CR |= (amplitudeOrMask << 24);
  }
  else if(waveType == TRIANGLE_WAVE)
  {
    Dac_reg->DAC_CR &= ~ (3 << 22);
    Dac_reg->DAC_CR |= (waveType << 22);
    Dac_reg->DAC_CR &= ~ (0xF << 24);
    Dac_reg->DAC_CR |= (amplitudeOrMask << 24);
  }
}
