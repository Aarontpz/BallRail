/*
 * MotorDriveTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */
#include "MotorDriveTask.h"
#include "share.h"

//-------------------------------------------------------------------------------------
/** @brief   Constructor which creates and initializes a MotorDrive task object.
 *  @details This constructor creates a FreeRTOS task with the given task run function,
 *           name, priority, and stack size. Its purpose is to set the appropriate
 *           motor driver pins depending on the PWM command, and shut down the motor
 *           if an unsafe condition was detected.
 *  @param   a_name A character string which will be the name of this task
 *  @param   a_priority The priority at which this task will initially run (default: 0)
 *  @param   a_stack_size The size of this task's stack in bytes
 *                        (default: @c configMINIMAL_STACK_SIZE)
 *  @param   p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which
 *                     can be used by this task to communicate (default: NULL)
 */
MotorDriveTask::MotorDriveTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

//-------------------------------------------------------------------------------------
/** @brief   The @c run() function for the MotorDrive task.
 *  @details This method is called by the RTOS scheduler. The function sets the IN pins
 *  		 on the motor driver to define the direction of the motor, depending on the
 *  		 sign of the PWM signal. If there's an unsafe condition, the motor driver will
 *  		 be set to BRAKE mode by pulling the IN pins low.
 */
void MotorDriveTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
	// initialize task variables upon system startup
	float pwm_level = 0;

	for (;;) {
		// get the PWM level that was set by the Controller Task
		pwm_level = p_motor_voltage_pwm -> get();
		if (!p_safe->get()) { //if p_safe is FALSE, go into SAFETY MODE
			GPIOB -> ODR &= ~GPIO_PIN_5;
			GPIOB -> ODR &= ~GPIO_PIN_4;
			LD2_GPIO_Port -> ODR |= LD2_Pin; //set display pin high for user awareness
		}
		else { //DRIVE ENABLE HIGH, NORMAL OPERATION
			LD2_GPIO_Port -> ODR ^= LD2_Pin;	// toggle display pin for user awareness
			if (pwm_level >= 0) { // drive motor forward
				GPIOB -> ODR |= GPIO_PIN_4;
				GPIOB -> ODR &= ~GPIO_PIN_5;
			}
			else { // drive motor backwards
				GPIOB -> ODR |= GPIO_PIN_5;
				GPIOB -> ODR &= ~GPIO_PIN_4;
			}
		}
		delay_from_for_ms(xLastWakeTime, 10); // delay that determines the timing of the task
	}
}


