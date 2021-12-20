
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

int red=0;
int green=1;
int blue=2;

static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);
}
/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters)
{
	//bool LedState = false;
	while (1)
	{
		Board_LED_Set(0, false);
		vTaskDelay(configTICK_RATE_HZ);
		Board_LED_Set(0, true);
		vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ / 2);
	}
}
static void vLEDTask2(void *pvParameters)
{
	vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ / 2);

	while (1)
	{
		Board_LED_Set(1, 0);
		vTaskDelay(configTICK_RATE_HZ);
		Board_LED_Set(1, 1);

		vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ / 2);
	}
}
static void vLEDTask3(void *pvParameters)
{
	vTaskDelay(3 * configTICK_RATE_HZ);
	while (1)
	{

		Board_LED_Set(2, 0);
		vTaskDelay(configTICK_RATE_HZ);
		Board_LED_Set(2, 1);

		vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ / 2);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	prvSetupHardware();

	/* LED1 toggle thread */
	xTaskCreate(vLEDTask1, (signed char* ) "vTaskLed1",
			configMINIMAL_STACK_SIZE,NULL, (tskIDLE_PRIORITY+3UL),
			(xTaskHandle *) NULL);

	/* LED2 toggle thread */
	xTaskCreate(vLEDTask2, (signed char* ) "vTaskLed2",
			configMINIMAL_STACK_SIZE,NULL, (tskIDLE_PRIORITY+2UL ),
			(xTaskHandle *) NULL);

	xTaskCreate(vLEDTask3, (signed char* ) "vTaskLed3",
			configMINIMAL_STACK_SIZE,NULL, (tskIDLE_PRIORITY+1UL),
			(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
