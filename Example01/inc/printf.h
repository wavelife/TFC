/*
 * --- file printf.h ---
 *
 * This is the file header for the printf module using UART output
 * @Author: Carles Saura
 */

#ifndef __PRINTF_MY_H
#define __PRINTF_MY_H

#include <stdint.h>
#include <stdarg.h>
/*-----------------------------------------------------------*/

/*
 * Simple function to init the baud rate and port of the UART.
 * @precondition baudrate contains a valid baudrate number (ie. 9600)
 *
 * @param port  		Port to initialize the connection
 * @param baudrate      The connection baudrate
 *
 * @return				1 if everything it's ok, 0 if the configuration is not unset after the invocation.
 */
uint8_t Printf_start( uint8_t port, uint32_t baudrate);

/*
 * Simple function to unset the configuration of the port of the UART and leave to other invocations be able
 * to change the bitrate. The port will be usefull after the invocation, but will be able to re-start it again
 * with another baudrate value.
 * @precondition baudrate contains a valid baudrate number (ie. 9600)
 *
 * @param port  		Port to unset de configuration
 */
void Printf_stop( uint8_t port );

/*
 * Simple function to write to the UART.
 * @precondition the str is a valid pointer and has enough space
 * @precondition the port represent a UART port pre initialized
 *
 * @param port  	Port to initialize the connection
 * @param trans_id  The transaction id. This is used if transaction mode is ON. Otherwise it must be set to 0.
 * @param str   	Pointer to destination buffer
 * @param format    A string with the formated text
 * @param ...       The variables to print, as many as the amount of variable symbols in the formated string, or more.
 */
void Printf_print(uint8_t port, uint8_t trans_id, char* str, const char* format, ...);

/*
 * Simple function to format a string using va_list as a input.
 * @precondition the str is a valid pointer and has enough space
 *
 * @param port  	Port to initialize the connection
 * @param trans_id  The transaction id. This is used if transaction mode is ON. Otherwise it must be set to 0.
 * @param str   	Pointer to destination buffer
 * @param format    A string with the formated text
 */
void Printf_vsprint(uint8_t port, uint8_t trans_id, char* str, const char* format, va_list listPointer);

/*
 * Simple function to read from the UART.
 * @precondition the str is a valid pointer and has enough space
 * @precondition the port represent a UART port pre initialized
 *
 * @param port  	Port to initialize the connection
 * @param string   	Pointer to source buffer
 * @param timeout   The amount of time to wait until read the buffer in ms.
 *
 * @return 			Returns the size of the buffer
 */
uint32_t Printf_scanf(uint8_t port, char* string, uint32_t timeout);

/*
 * Simple function to set transaction mode to on. This is used to allow to print only the invocations
 * with the returned id. If transaction mode is on, only the invocations with the returned id will be
 * able to print, the other invocation will remain in sleep mode until transaction mode will be set to
 * off.
 *
 * @return  		a value from 1 to 255 if the transaction mode is avaliable, otherwise 0.
 */
uint8_t Printf_transactionOn();

/*
 * Simple function to set transaction mode to off
 *
 */
void Printf_transactionOff();

/*
 * Simple function to (active) wait the amount of ms.
 *
 * @param ms   The amount of time to wait in ms.
 */
void Printf_delayMs( uint32_t ms);

/*-----------------------------------------------------------*/
#endif
