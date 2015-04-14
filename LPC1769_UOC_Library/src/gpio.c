/*
 * This is the file implementation for the GPIO module
 * @Author: Carles Saura
 */

#include "LPC17xx.h"
#include "gpio.h"

/*-----------------------------------------------------------*/
/*
 * Simple function to init the LED on the LPCXpresso LPC17xx board.
 */
void GPIO_init( unsigned long pin, unsigned long port )
{
	LPC_PINCON->PINSEL1	&= pin;
	LPC_GPIO0->FIODIR |= port;
}

/*
 * Simple function to get the state of the port.
 */
unsigned long GPIO_getState()
{
	return LPC_GPIO0->FIOPIN;
}

/*
 * Simple function to turn the LED on.
 */
void GPIO_makeOut( unsigned long clr, unsigned long set )
{
	LPC_GPIO0->FIOCLR = clr;
	LPC_GPIO0->FIOSET = set;
}
