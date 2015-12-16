#ifndef __Rcc_H__
#define __Rcc_H__

#include <stdint.h>
#include "Gpio.h"
//#include "Dac.h"
// #include "Gpio.h"

typedef struct RCC_t RCCtype;
struct RCC_t
{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	volatile uint32_t RCC_AHB3RSTR;
	volatile uint32_t RESERVE_0;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RESERVE_1;
	volatile uint32_t RESERVE_2;
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	volatile uint32_t RCC_AHB3ENR;
	volatile uint32_t RESERVE_3;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RESERVE_4;
	volatile uint32_t RESERVE_5;
	volatile uint32_t RCC_AHB1LPENR;
	volatile uint32_t RCC_AHB2LPENR;
	volatile uint32_t RCC_AHB3LPENR;
	volatile uint32_t RESERVE_6;
	volatile uint32_t RCC_APB1LPENR;
	volatile uint32_t RCC_APB2LPENR;
	volatile uint32_t RESERVE_7;
	volatile uint32_t RESERVE_8;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	volatile uint32_t RESERVE_9;
	volatile uint32_t RESERVE_10;
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	volatile uint32_t RCC_PLLSAICFGR;
	volatile uint32_t RCC_DCKCFGR;
};

#define RCC_reg ((RCCtype *)0x40023800)

#define GPIOx_ENABLE_CLOCK(x)	(0x00100000 | (1 << (x)))
#define GPIOx_RESET(x)			  (1 << (x))

#define ENABLE_APB1_PRESCALE	((RCC_reg->RCC_CFGR >> 12) & 1)

#define INTERNAL_CLOCK    16000000
#define CRYSTAL_CLOCK     8000000

void gpioUnresetEnableClock(GPIO *port);
void dacUnresetEnableClock();
void timer6UnresetEnableClock();
void dma1UnresetEnableClock();

uint32_t getSystemClock();
uint32_t getAPB1Clock(uint32_t sysClock);
// void rngUnresetEnableClock();

#endif // __Rcc_H__
