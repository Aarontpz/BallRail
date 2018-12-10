/*
 * LimitSwitchTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "LimitSwitchTask.h"
#include "share.h"

//-------------------------------------------------------------------------------------
/** @brief   Constructor which creates and initializes a LimitSwitch task object.
 *  @details This constructor creates a FreeRTOS task with the given task run function,
 *           name, priority, and stack size. Its purpose is to alarm the system of an
 *           unsafe condition if a limit switch drives a digital pin low.
 *  @param   a_name A character string which will be the name of this task
 *  @param   a_priority The priority at which this task will initially run (default: 0)
 *  @param   a_stack_size The size of this task's stack in bytes
 *                        (default: @c configMINIMAL_STACK_SIZE)
 *  @param   p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which
 *                     can be used by this task to communicate (default: NULL)
 */
LimitSwitchTask::LimitSwitchTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

//-------------------------------------------------------------------------------------
/** @brief   The @c run() function for the LimitSwitch task.
 *  @details This method is called by the RTOS scheduler. The function reads a GPIO
 *  		 pin and triggers an unsafe condition if the pin is pulled low. The condition
 *  		 is updated in the p_safe shared variable.
 */
void LimitSwitchTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
	// initialize task variables upon system startup
	bool triggered = false;
	bool current_safe = true;
	for (;;) {
		// read GPIO pin and set NOT SAFE CONDITION if pin is driven low
		triggered = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET;
		current_safe = p_safe->get() && !triggered;
		p_safe->put(current_safe);
		delay_from_for_ms(xLastWakeTime, 1); // delay that determines the timing of the task
	}
}