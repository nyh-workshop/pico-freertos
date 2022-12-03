#include <stdio.h>
#include "pico/stdlib.h"

// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#define LED_PIN_1 8
#define LED_PIN_2 (LED_PIN_1 + 1)

/* Prototypes for the standard FreeRTOS callback/hook functions implemented
within this file. */
void vApplicationMallocFailedHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );

void task1_handle(void *p);
void task2_handle(void *p);

TaskHandle_t htask1 = NULL;
TaskHandle_t htask2 = NULL;

int main()
{
    stdio_init_all();

    puts("Hello world RP2040 FreeRTOS!\n");

	gpio_init(LED_PIN_1);
    gpio_set_dir(LED_PIN_1, GPIO_OUT);

	gpio_init(LED_PIN_2);
    gpio_set_dir(LED_PIN_2, GPIO_OUT);

    xTaskCreate(task1_handle, "task1", 512, NULL, 1, &htask1);
	xTaskCreate(task2_handle, "task2", 512, NULL, 1, &htask2);

    vTaskStartScheduler();

	while(1);

    return 0;
}

void task1_handle(void *p)
{
	while(1)
	{
		gpio_put(LED_PIN_1, 0);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		gpio_put(LED_PIN_1, 1);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void task2_handle(void *p)
{
	while(1)
	{
		gpio_put(LED_PIN_2, 0);
		vTaskDelay(500 / portTICK_PERIOD_MS);
		gpio_put(LED_PIN_2, 1);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}