#ifndef __Dac_H__
#define __Dac_H__

#include <stdint.h>

typedef struct DAC_t DACtype;
struct DAC_t{
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

void dacChannelxEnable(int channelX);
void dacOutputBufferxEnable(int channelX);

#endif // __Dac_H__
