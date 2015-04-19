/*
 * --- file printf.h ---
 *
 * This is the file header for the log module using UART output
 * @Author: Carles Saura
 */

#ifndef __LOG_H
#define __LOG_H

#include <stdint.h>

/*-----------------------------------------------------------*/
/*
 * Simple function to init the baud rate and port of the UART.
  * @precondition baudrate contains a valid baudrate number (ie. 9600)
 *
 * @param port  		Port to initialize the connection
 * @param baudrate      The connection baudrate
 */
void Log_start( uint8_t  port, uint32_t baudrate);

/*
 * Simple function to write to the UART.
 * @precondition the str is a valid pointer and has enough space
 *
 * @param str   	Pointer to destination buffer
 * @param format    A string with the formated text
 * @param ...       The variables to print, as many as the amount of variable symbols in the formated string, or more.
 */
void Log_log(char* str, const char* format, ...);

/*-----------------------------------------------------------*/
#endif
