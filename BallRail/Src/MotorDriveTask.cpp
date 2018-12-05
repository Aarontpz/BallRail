/*
 * MotorDriveTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */
#include "MotorDriveTask.h"
#include "share.h"

MotorDriveTask::MotorDriveTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

void MotorDriveTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
//	bool triggered = false;
//	bool safe_state = true;
	float pwm_level = 0;

	for (;;) {
		pwm_level = p_motor_voltage_pwm -> get();

		if (pwm_level >= 0) {
			// set Pin 4 PWM = 0
			// set Pin 5 PWM = pwm_level
		}
		else {
			// set Pin 4 PWM = -pwm_level
			// set Pin 5 PWM = 0
		}

//		triggered = !(GPIOA -> IDR & GPIO_PIN_9); //active low
//		triggered = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET;
//		safe_state = safe_state && !triggered;
//		p_safe -> put(safe_state);
//		safe_state = p_safe->get();
		if (!p_safe->get()) { //if p_safe is FALSE, go into SAFETY MODE
			// DRIVE ENA LOW
//			GPIOA -> ODR &= ~GPIO_PIN_10;
			LD2_GPIO_Port -> ODR |= LD2_Pin; //set display pin high
		}
		else { //DRIVE ENABLE HIGH, NORMAL OPERATION
//			GPIOA -> ODR |= GPIO_PIN_10; //DRIVE ENA HIGH
			LD2_GPIO_Port -> ODR ^= LD2_Pin;
		}

//		if (LD2_GPIO_Port -> ODR & LD2_Pin) { //forward
//			GPIOB -> ODR |= GPIO_PIN_4;
//			GPIOB -> ODR &= ~GPIO_PIN_5;
//		}
//		else { //backwards
//			GPIOB -> ODR |= GPIO_PIN_5;
//			GPIOB -> ODR &= ~GPIO_PIN_4;
//		}
		delay_from_for_ms(xLastWakeTime, 20); //delay for 20ms
	}
}


