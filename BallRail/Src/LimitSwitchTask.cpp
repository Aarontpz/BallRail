/*
 * LimitSwitchTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "LimitSwitchTask.h"
#include "share.h"

LimitSwitchTask::LimitSwitchTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

void LimitSwitchTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
	bool triggered = false;
	bool current_safe = true;
	for (;;) {
		triggered = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET;
		current_safe = p_safe->get() && !triggered;
		p_safe->put(current_safe);
		delay_from_for_ms(xLastWakeTime, 1); //delay for 50ms
	}
}
