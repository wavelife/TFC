/*
 * This is the file header for the log module using UART output
 * @Author: Carles Saura
 */
#include <stdint.h>

/*-----------------------------------------------------------*/
/*
 * Simple function to init the baud rate and port of the UART.
 */
void logStart( uint8_t  port, uint32_t baudrate);

/*
 * Simple function to write to the UART.
 */
void logLog(char* str, const char* format, ...);

/*-----------------------------------------------------------*/
