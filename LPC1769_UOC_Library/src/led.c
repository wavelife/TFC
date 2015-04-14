/*
 * This is the file implementation for the led module
 * @Author: Carles Saura
 */

#include "led.h"
#include "gpio.h"

/*-----------------------------------------------------------*/

/*
 * Simple function to init the LED on the LPCXpresso LPC17xx board.
 */
void led_init( void )
{
	GPIO_init(( ~( 3 << 12 ) ), ( 1 << mainLED_BIT ));
}

/*
 * Simple function to turn the LED on.
 */
void led_on( void )
{
	/* Turn the LED on. */
	GPIO_makeOut(( 1 << mainLED_BIT ), ( 1 << mainLED_BIT ));

}

/*
 * Simple function to turn the LED off.
 */
void led_off( void )
{
	/* Turn the LED off. */
	GPIO_makeOut(( 1 << mainLED_BIT ), 0);
}

/*
 * Simple function to toggle the LED.
 */
void led_toggle( void )
{
	unsigned long ulLEDState;

	/* Obtain the current P0 state. */
	ulLEDState = GPIO_getState();

	/* Turn the LED off if it was on, and on if it was off. */
	if((ulLEDState & ( 1 << mainLED_BIT )) == 0)
	{
		led_on();
	}
	else
	{
		led_off();
	}
}
/*-----------------------------------------------------------*/


