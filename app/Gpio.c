#include "Gpio.h"
#include "Rcc.h"
#include "stm32f4xx_hal_rcc.h"

/**
 * brief @ This function is to configure I/O pins as analogue mode.
 *
 * param 1 @ pinNum - is the pin number of the port
 * param 2 @ port   - is the port to configure
 */
void configureAnalog(int pinNum, GPIO *port){
	gpioUnresetEnableClock(port);
	port->MODER |= GPIO_MODE_ANALOG << (pinNum * 2);
	port->PUPDR &= ~(3 << (pinNum * 2));		//MASK PUPDR reg and clear respective bits
	port->PUPDR |= NO_PULL << (pinNum * 2);
}


/**
 * brief @ This function is to configure the pin as Output pin.
*
 * param 1 @ speed  - is the output mode
 * param 2 @ pinNum	-	is the pin number of the port
 * param 3 @ port	- is the port to configure
 */
void configureOutput(int speed, int pinNum, GPIO *port){

	gpioUnresetEnableClock(port);

	port->MODER &= ~(3 << (pinNum * 2));		//MASK MODER reg and CLEAR selected bits
	port->MODER |= GPIO_MODE_OUTPUT << (pinNum * 2);
	port->OTYPER &= ~(1 << (pinNum));
	port->OSPEED &= ~(3 << (pinNum * 2));
	port->OSPEED |= speed << (pinNum * 2);
}


void writeOne(uint16_t pinNum, GPIO *port)
{
	port->BSRR = 1 << pinNum;
}

void writeZero(uint16_t pinNum, GPIO *port)
{
	port->BSRR = 1 << (pinNum + 16);
}


// void readPin(uint16_t readPinNumber, GPIO *readPort, uint16_t writePin, GPIO *writePort)
// {
	// int signal = readPort->IDR & (1 << readPinNumber);
	// if(signal)
		// writeOne(writePin, writePort);
	// else
		// writeZero(writePin, writePort);
// }


