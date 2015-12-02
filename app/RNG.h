#ifndef __RNG_H__
#define __RNG_H__

#include <stdint.h>
#include "Rcc.h"


typedef struct RNG_t RNGtype;
struct RNG_t
{
	volatile uint32_t RNG_CR;
	volatile uint32_t RNG_SR;
	volatile uint32_t RNG_DR;
};

#define RNG_reg ((RNGtype *)0x50060800)

void enableRNG();
int readyToRead();
#endif // __RNG_H__
