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


/*-----------------------------------------------------------*/
/*
 * Simple function to init the baud rate and port of the UART.
 */
void logStart( uint8_t  port, uint32_t baudrate){
	 printfStart( port, baudrate);
}

/*
 * Simple function to write the log to the UART.
 */
void logLog(char* str, const char* format, ...){
	const char *logHead = "\n***********************************\nText Log:\n\b";
	const char *logEnd = "\n********************************end\n\n";
	va_list listPointer;
	/* This is used to transmit the variable parameters */
	va_start( listPointer, format );

	printfPrint(str,logHead, listPointer );
	printfVsprint(str,format, listPointer );
	printfPrint(str,logEnd, listPointer );
}


/*-----------------------------------------------------------*/
