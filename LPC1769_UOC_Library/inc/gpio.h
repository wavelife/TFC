/*
 * This is the file header for the GPIO module
 * @Author: Carles Saura
 */

/*-----------------------------------------------------------*/
/*
 * Simple function to init the LED on the LPCXpresso LPC17xx board.
 */
void GPIO_init( unsigned long pin, unsigned long port );

/*
 * Simple function to get the state of the port.
 */
unsigned long GPIO_getState();

/*
 * Simple function to turn the LED on.
 */
void GPIO_makeOut( unsigned long clr, unsigned long set );
