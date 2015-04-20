/*
    FreeRTOS V8.0.1 - Copyright (C) 2014 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* Library includes. */
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Demo includes. */
#include "basic_io.h"


/* The tasks to be created.  Two instances are created of the sender task while
only a single instance is created of the receiver task. */
static void vSenderTask( void *pvParameters );
static void vReceiverTask( void *pvParameters );

#define _MAX_NUMBER_STACKS_IN_QUEUE 20

/*-----------------------------------------------------------*/

/* Declare a variable of type xQueueHandle.  This is used to store the queue
that is accessed by all three tasks. */
xQueueHandle xQueue;
/* Declare a variable of type xSemaphoreHandle.  This is used to reference the
mutex type semaphore that is used to ensure mutual exclusive access to stdout. */
xSemaphoreHandle xMutex;

char str[30];

int main( void )
{
	/* Init the semi-hosting. This is to debug only */
	printf( "\n" );
	/* Initiate the UART port to print */
	Log_start(3, 115200);
    /* The queue is created to hold a maximum of 5 long values. */
    xQueue = xQueueCreate( _MAX_NUMBER_STACKS_IN_QUEUE, sizeof( int ) );
    /* Before a semaphore is used it must be explicitly created. */
	xMutex = xSemaphoreCreateMutex();
	//vSemaphoreCreateBinary( xMutex );
	/* Take the semaphore to prevent acces to the Queue when is full */
	//xSemaphoreTake( xMutex, portMAX_DELAY );
	/* The tasks are going to use a pseudo random delay, seed the random number
	generator. */
	srand( 435 );

	if( xQueue != NULL && xMutex != NULL )
	{
		//xSemaphoreTake( xMutex, 10 );
		/* Create two instances of the task that will write to the queue.  The
		parameter is used to pass the value that the task should write to the queue,
		so one task will continuously write 100 to the queue while the other task
		will continuously write 200 to the queue.  Both tasks are created at
		priority 1. */
		xTaskCreate( vSenderTask, "Sender1", 240, ( void * ) 1, 2, NULL );
		xTaskCreate( vSenderTask, "Sender2", 240, ( void * ) 2, 2, NULL );

		/* Create the task that will read from the queue.  The task is created with
		priority 2, so above the priority of the sender tasks. */
		xTaskCreate( vReceiverTask, "Receiver", 240, NULL, 3, NULL );

		/* Start the scheduler so the created tasks start executing. */
		vTaskStartScheduler();
	}
	else
	{
		/* The queue could not be created. */
		vPrintString( "The queue could not be created.\r\n" );
		Log_start(3, 115200);
		Log_log( str, "The queue could not be created.\r\n" );
	}

    /* If all is well we will never reach here as the scheduler will now be
    running the tasks.  If we do reach here then it is likely that there was
    insufficient heap memory available for a resource to be created. */
	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/

static void vSenderTask( void *pvParameters )
{
long instance_id;
portBASE_TYPE xStatus;
char str[30];
int toSend;

	/* Two instances are created of this task so the value that is sent to the
	queue is passed in via the task parameter rather than be hard coded.  This way
	each instance can use a different value.  Cast the parameter to the required
	type. */
	instance_id = ( long ) pvParameters;

	/* As per most tasks, this task is implemented within an infinite loop. */
	for( ;; )
	{
		/* The random generated number to enqueue */
		toSend = rand();
		/* The first parameter is the queue to which data is being sent.  The
		queue was created before the scheduler was started, so before this task
		started to execute.

		The second parameter is the address of the data to be sent.

		The third parameter is the Block time � the time the task should be kept
		in the Blocked state to wait for space to become available on the queue
		should the queue already be full.  In this case we don�t specify a block
		time because there should always be space in the queue. */
		xStatus = xQueueSendToBack( xQueue, &toSend, 0 );

		if( xStatus != pdPASS )
		{
			/* We could not write to the queue because it was full. Send a message to inform about it */
			vPrintStringAndNumber( "Could not send to the queue.\r\n", instance_id );
			Log_start(3, 115200);
			Log_log( str, "Could not send to the queue. Sender %d\n. Value: %d\n", instance_id, toSend );
			/* Give the semaphore to mark as resource busy */
			xSemaphoreTake( xMutex, 0 );
			/* Wait until Queue will be empty */
			while ( xSemaphoreTake( xMutex, 100 ) != pdTRUE){
				//vPrintStringAndNumber( "Sleeping! Sender: ", instance_id );
				//taskYIELD();
			}
			vPrintStringAndNumber( "Awake! Sender: ", instance_id );
			xStatus = xQueueSendToBack( xQueue, &toSend, 0 );
			xSemaphoreGive( xMutex );

			/* Allow the other sender task to execute. */
			//taskYIELD();
			//vTaskDelay( 1000 );
		}
		else{
			//xSemaphoreGive( xMutex );
			vPrintStringAndNumber( "Queued! Sender: ", instance_id );
			/* Allow the other sender task to execute. */
			//taskYIELD();
			//vTaskDelay( 100/portTICK_RATE_MS );
		}
		/* Allow the other sender task to execute. */
		taskYIELD();
	}
}
/*-----------------------------------------------------------*/

static void vReceiverTask( void *pvParameters )
{
/* Declare the variable that will hold the values received from the queue. */
long lReceivedValue;
portBASE_TYPE xStatus;
const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
char str[30];

	/* This task is also defined within an infinite loop. */
	for( ;; )
	{
		/* As this task unblocks immediately that data is written to the queue this
		call should always find the queue empty. */
		switch ( uxQueueMessagesWaiting( xQueue ) )
				{
				case 0:
					vPrintString( "Queue is empty\r\n" );
					Log_log( str, "Queue is empty\r\n" );
					vTaskDelay( xTicksToWait );
					break;
				case _MAX_NUMBER_STACKS_IN_QUEUE:
					while ( uxQueueMessagesWaiting( xQueue ) != 0 ){
						xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );
						if( xStatus == pdPASS )
							vPrintString( "The Queue was full\n" );
							Log_start(3, 115200);
							Log_log( str, "The Queue was full. Value = %d\n", lReceivedValue );
					}
					xSemaphoreGive( xMutex );

					/* Allow the sender task to execute. */
					//taskYIELD();
					//xSemaphoreTake( xMutex, portMAX_DELAY );
					break;
				default:
					/* The first parameter is the queue from which data is to be received.  The
					queue is created before the scheduler is started, and therefore before this
					task runs for the first time.

					The second parameter is the buffer into which the received data will be
					placed.  In this case the buffer is simply the address of a variable that
					has the required size to hold the received data.

					the last parameter is the block time � the maximum amount of time that the
					task should remain in the Blocked state to wait for data to be available should
					the queue already be empty. */
					//xSemaphoreGive( xMutex );
					xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );

					if( xStatus == pdPASS )
					{
						/* Data was successfully received from the queue, print out the received
						value. */
						vPrintStringAndNumber( "Received = ", lReceivedValue );
						Log_start(3, 115200);
						Log_log( str, "Received = %d", lReceivedValue );
					}
					break;
				}
/*		if( uxQueueMessagesWaiting( xQueue ) != 0 )
		{
			vPrintString( "Queue should have been empty!\r\n" );
			Log_start(3, 115200);
			Log_log( str, "Queue should have been empty!\r\n" );
		}*/


//		else
//		{
//			/* We did not receive anything from the queue even after waiting for 100ms.
//			This must be an error as the sending tasks are free running and will be
//			continuously writing to the queue. */
//			vPrintString( "Could not receive from the queue.\r\n" );
//			Log_start(3, 115200);
//			Log_log( str, "Could not receive from the queue.\r\n" );
//		}
	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}

