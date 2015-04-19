/*
 * This is the file implementation for the log module using UART output
 * @Author: Carles Saura
 */
#include "log.h"
/* CLib includes */
#include <stdint.h>
#include <stdarg.h>
#ifndef INC_FREERTOS_H
	#include "FreeRTOS.h"
#endif
#ifndef TASK_H
	#include "task.h"
#endif
/* to print using UART include */
#include "printf.h"
uint8_t uart_port = 3;
portTickType pxPreviousWakeTime = -1;
/* The rate at which data is sent to the queue, specified in milliseconds. */
#define logTIME_TO_WAIT			( 100 / portTICK_RATE_MS )

/*-----------------------------------------------------------*/

void Log_start( uint8_t  port, uint32_t baudrate){
	 Printf_start( port, baudrate);
	 uart_port = port;
	 /* Initialise pxPreviousWakeTime - this only needs to be done once. */
	 if ( pxPreviousWakeTime != -1 )
		 pxPreviousWakeTime = xTaskGetTickCount();
}


void Log_log(char* str, const char* format, ...){
	const char *logHead = "\n***********************************\nText Log:\n\b";
	const char *logEnd = "\n*******************************end*\n\n";
	uint8_t trans_id;
	va_list listPointer;
	/* This is used to transmit the variable parameters */
	va_start( listPointer, format );
	/* Enable transaction mode */
	trans_id = Printf_transactionOn();
	while ( trans_id == 0 ){
		/* Wait */
		vTaskDelayUntil( &pxPreviousWakeTime, logTIME_TO_WAIT );
		trans_id = Printf_transactionOn();
	}
	Printf_print( uart_port, trans_id, str, logHead, listPointer );
	Printf_vsprint( uart_port, trans_id, str,format, listPointer );
	Printf_print( uart_port, trans_id, str, logEnd, listPointer );
	Printf_transactionOff();
}

/*-----------------------------------------------------------*/
