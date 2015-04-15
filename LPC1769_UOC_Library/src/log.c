/*
 * This is the file implementation for the log module using UART output
 * @Author: Carles Saura
 */
#include "log.h"
/* CLib includes */
#include <stdint.h>
#include <stdarg.h>
/* to print using UART include */
#include "printf.h"
uint8_t uart_port = 3;

/*-----------------------------------------------------------*/

void Log_start( uint8_t  port, uint32_t baudrate){
	 Printf_start( port, baudrate);
	 uart_port = port;
}

void Log_log(char* str, const char* format, ...){
	const char *logHead = "\n***********************************\nText Log:\n\b";
	const char *logEnd = "\n********************************end\n\n";
	va_list listPointer;
	/* This is used to transmit the variable parameters */
	va_start( listPointer, format );

	Printf_print( uart_port, str,logHead, listPointer );
	Printf_vsprint( uart_port, str,format, listPointer );
	Printf_print( uart_port, str,logEnd, listPointer );
}

/*-----------------------------------------------------------*/
