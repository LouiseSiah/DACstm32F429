#include "Rcc.h"

void gpioUnresetEnableClock(GPIO *port)
{
  int positionPort = ((int)port - (0x40020000))/(0x400);

	RCC_reg->RCC_AHB1RSTR	&= ~GPIOx_RESET(positionPort);
	RCC_reg->RCC_AHB1ENR	|= GPIOx_ENABLE_CLOCK(positionPort);
}

void dacUnresetEnableClock()
{
  RCC_reg->RCC_APB1RSTR &= ~ (1 << 29);
  RCC_reg->RCC_APB1ENR |= (1 << 29);
}

void timer6UnresetEnableClock()
{
	RCC_reg->RCC_APB1RSTR &= ~ (1 << 4);
	RCC_reg->RCC_APB1ENR |= (1 << 4);
}

uint32_t getSystemClock(){
	int divM, xN, divP, divAHB;
	int sysClock;
	int enbAHBPrescale = RCC_reg->RCC_CFGR & 256;

	if(enbAHBPrescale == 0)
		divAHB = 1;
	else
		divAHB = 1 << (((RCC_reg->RCC_CFGR >> 4) & 7) + 1);

	xN = (RCC_reg->RCC_PLLCFGR >> 6) & 511;
	divM = (RCC_reg->RCC_PLLCFGR & 63);
	divP = 1 << (((RCC_reg->RCC_PLLCFGR >> 16) & 3) + 1);

	if(((RCC_reg->RCC_CFGR & 0xC) >> 2) == 0)
		sysClock = INTERNAL_CLOCK / divAHB;
	else if(((RCC_reg->RCC_CFGR & 0xC) >> 2) == 1)
		sysClock = CRYSTAL_CLOCK / divAHB;
	else {
		if(((RCC_reg->RCC_PLLCFGR >> 22) & 1) == 0)
			sysClock = (INTERNAL_CLOCK * xN) / (divM * divP * divAHB);
		else
			sysClock = (CRYSTAL_CLOCK) / (divM * divP * divAHB) * xN;
	}

	return sysClock;
}

uint32_t getAPB1Clock(uint32_t sysClock){
	int divAPB1, aPB1Clock;

	if(ENABLE_APB1_PRESCALE)
		divAPB1 = 1 << (((RCC_reg->RCC_CFGR >> 10) & 3) + 1);
	else
		divAPB1 = 1;

	aPB1Clock = sysClock / divAPB1;

	return aPB1Clock;
}

void dma1UnresetEnableClock()
{
	int read;
	RCC_reg->RCC_AHB1RSTR &= ~ (1  << 21);
	read = RCC_reg->RCC_AHB1RSTR ;
	RCC_reg->RCC_AHB1ENR |= (1 << 21);
	read = RCC_reg-> RCC_AHB1ENR;

}

// void rngUnresetEnableClock(){
	// RCC_reg->RCC_AHB2RSTR &= ~(1 << 6);
	// RCC_reg->RCC_AHB2ENR  |= (1 << 6);

//	RCC_reg->RCC_PLLCFGR &= ~(15 << 24);	//CLEAR PLLQ
//	RCC_reg->RCC_PLLCFGR |= (3 << 24);		//set PLLQ to 0011
// }
