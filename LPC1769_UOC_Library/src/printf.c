/*
 * --- file printf.c ---
 *
 * This is the file implementation for the printf module using UART output
 * @Author: Carles Saura
 */
#include "printf.h"
/* CLib includes */
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
/* LPC includes */
#include "LPC17xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"

extern volatile uint32_t UART0Count, UART1Count, UART2Count, UART3Count;
extern volatile uint8_t UART0Buffer, UART1Buffer, UART2Buffer, UART3Buffer;
volatile uint32_t *lpc_uart_ier;
volatile uint32_t *uart_count;
volatile uint8_t *uart_buffer;
uint8_t uart_port;
uint32_t uart_baudrate = 9600;
xSemaphoreHandle *xSemUART;
xSemaphoreHandle xSemUART0 = NULL;
xSemaphoreHandle xSemUART1 = NULL;
xSemaphoreHandle xSemUART2 = NULL;
xSemaphoreHandle xSemUART3 = NULL;

void Printf_start( uint8_t  port, uint32_t baudrate){

	/* opening port */
	UARTInit(port, baudrate);
	/* Setting global variables */
	uart_port = port;
	switch(port){
	case 0: lpc_uart_ier = &LPC_UART0->IER;
		uart_count = &UART0Count;
		uart_buffer = &UART0Buffer;
		uart_baudrate = baudrate;
		xSemUART = &xSemUART0;
		break;
	case 1: lpc_uart_ier = &LPC_UART1->IER;
		uart_count = &UART1Count;
		uart_buffer = &UART1Buffer;
		uart_baudrate = baudrate;
		xSemUART = &xSemUART1;
		break;
	case 2: lpc_uart_ier = &LPC_UART2->IER;
		uart_count = &UART2Count;
		uart_buffer = &UART2Buffer;
		uart_baudrate = baudrate;
		xSemUART = &xSemUART2;
		break;
	default:
	case 3: lpc_uart_ier = &LPC_UART3->IER;
		uart_count = &UART3Count;
		uart_buffer = &UART3Buffer;
		uart_baudrate = baudrate;
		xSemUART = &xSemUART3;
		break;
	}
	/* Initiate the semphr */
	if( *xSemUART == NULL) vSemaphoreCreateBinary( *xSemUART );
}


/*
 * Simple function to write to the UART.
 * @precondition 	str is a valid pointer
 * @precondition 	if port contains a non pre intitialized port, baudrate will be initialized at default value (9600)
 *
 * @param port  	Port to initialize the connection
 * @param str   	Pointer to destination buffer
 * @param format    A string with the formated text
 */
void printf_send(uint8_t port, char* str, int bufsz){

	Printf_start(port, uart_baudrate);

	if( *xSemUART != NULL ){
		if (bufsz > BUFSIZE) bufsz = BUFSIZE;			/* This is to prevent buffer overflow */

		while( xSemaphoreTake( *xSemUART, ( portTickType ) 10 ) != pdTRUE ){}			/*  Wait and protect the function from other invocations */

		*lpc_uart_ier = IER_THRE | IER_RLS;				/* Disable RBR */
		UARTSend(uart_port, (uint8_t *)str , bufsz );
		*uart_count = 0;
		/* Give the Semphr and enable the function to others invocations */
		xSemaphoreGive( *xSemUART );
	}
}

void Printf_print( uint8_t port, char* str, const char* format, ... ){
	int bufsz;

	va_list listPointer;
	/* This is used to transmit the variable parameters */
	va_start( listPointer, format );
	bufsz = vsprintf(str, format, listPointer);
	va_end( listPointer );
	printf_send( port, str, bufsz);
}

void Printf_vsprint( uint8_t port, char* str, const char* format, va_list listPointer ){
	int bufsz;

	bufsz = vsprintf(str, format, listPointer);
	printf_send( port, str, bufsz);
}


uint32_t Printf_scanf( uint8_t port, char* string, uint32_t timeout ){
	uint32_t oldCount = 0, newCount = 0;

	Printf_start( port, uart_baudrate );

	if( *xSemUART != NULL ){
		while( xSemaphoreTake( *xSemUART, ( portTickType ) 10 ) != pdTRUE ){}			/* Wait and protect the function from other invocations */

		*uart_count = 0; // clean buff
		*lpc_uart_ier = IER_THRE | IER_RLS | IER_RBR; // enable interrupt RX UART

		Printf_delayMs(timeout); // wait sometime for receive some commands
		do{
			oldCount = newCount;
			Printf_delayMs(5);
			newCount = *uart_count;
		}while( oldCount != newCount ); // wait a little time while we have new chars
		*lpc_uart_ier = IER_THRE | IER_RLS; // disable interrupt RX UART
		if(newCount==0){
			/* Give the Semphr and enable the function to others invocations */
			xSemaphoreGive( *xSemUART );
			strncpy(string, '\0', 1 );
			return 0;
		}
		strncpy( string, (char*)uart_buffer, newCount );
		string[newCount] = 0; // add end string. Now we have a string
		*uart_count = 0; // clean buff
		*uart_buffer = '\0';
		/* Give the Semphr and enable the function to others invocations */
		xSemaphoreGive( *xSemUART );

		return newCount;
	}
	else return 0;
}

void Printf_delayMs( uint32_t ms){
	int i;
	//7140 iterations are 1ms aprox (it's a vulgar implementation)
	for(i = 0; i < ( ((uint32_t)7140)*ms); i++){ ;
	}

}
/*-----------------------------------------------------------*/
