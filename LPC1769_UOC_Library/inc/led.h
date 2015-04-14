/*
 * This is the file header for the led module
 * @Author: Carles Saura
 */

/* The bit of port 0 that the LPCXpresso LPC13xx LED is connected. */
#define mainLED_BIT 						( 22 )
/*-----------------------------------------------------------*/
/*
 * Simple function to init the LED on the LPCXpresso LPC17xx board.
 */
void led_init( void );

/*
 * Simple function to turn the LED on.
 */
void led_on( void );

/*
 * Simple function to turn the LED off.
 */
void led_off( void );

/*
 * Simple function to toggle the LED.
 */
void led_toggle( void );
/*-----------------------------------------------------------*/
