/*
 * --- file printf.h ---
 *
 * This is the file header for the printf module using UART output
 * @Author: Carles Saura
 */

#ifndef __PRINTF_H
#define __PRINTF_H

#include <stdint.h>
#include <stdarg.h>
/*-----------------------------------------------------------*/

/*
 * Simple function to init the baud rate and port of the UART.
 * @precondition baudrate contains a valid baudrate number (ie. 9600)
 *
 * @param port  		Port to initialize the connection
 * @param baudrate      The connection baudrate
 */
void Printf_start( uint8_t  port, uint32_t baudrate);

/*
 * Simple function to write to the UART.
 * @precondition the str is a valid pointer and has enough space
 *
 * @param port  	Port to initialize the connection
 * @param str   	Pointer to destination buffer
 * @param format    A string with the formated text
 * @param ...       The variables to print, as many as the amount of variable symbols in the formated string, or more.
 */
void Printf_print(uint8_t port, char* str, const char* format, ...);

/*
 * Simple function to format a string using va_list as a input.
 * @precondition the str is a valid pointer and has enough space
 *
 * @param port  	Port to initialize the connection
 * @param str   	Pointer to destination buffer
 * @param format    A string with the formated text
 */
void Printf_vsprint(uint8_t port, char* str, const char* format, va_list listPointer);

/*
 * Simple function to read from the UART.
 * @precondition the str is a valid pointer and has enough space
 *
 * @param port  	Port to initialize the connection
 * @param string   	Pointer to source buffer
 * @param timeout   The amount of time to wait until read the buffer in ms.
 *
 * @return 			Returns the size of the buffer
 */
uint32_t Printf_scanf(uint8_t port, char* string, uint32_t timeout);

/*
 * Simple function to (active) wait the amount of ms.
 *
 * @param ms   The amount of time to wait in ms.
 */
void Printf_delayMs( uint32_t ms);

/*-----------------------------------------------------------*/
#endif
