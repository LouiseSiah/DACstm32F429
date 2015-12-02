#include "Dac.h"

/**
 * brief @ This function is to configure I/O pins as analogue mode.
 *
 * param 1 @ pinNum - is the pin number of the port
 * param 2 @ port   - is the port to configure
 */
void dacChannelEnable(int channelX)
{
  if(channelX == 1)
    Dac_reg->DAC_CR |= 1; 
  else if (channelX == 2)
    Dac_reg->DAC_CR |= (1 << 16); 
  else
    return;
  
}

void dacOutputBufferxEnable(int channelX);
