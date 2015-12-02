#include "RNG.h"

void enableRNG(){
	rngUnresetEnableClock();
	RNG_reg->RNG_CR |= (1 << 2);
}

int readyToRead()
{
	int error, pass;
	error = RNG_reg->RNG_SR & 0x00000002;

	if(error)
		return 0;

	error = RNG_reg->RNG_SR & 0x00000004;

	if(error)
		return 0;

	pass = RNG_reg->RNG_SR & 0x00000001;

	if(pass)
		return 1;
	else
		return 0;
}
