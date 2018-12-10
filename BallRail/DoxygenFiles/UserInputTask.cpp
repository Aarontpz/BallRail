/*
 * UserInputTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "UserInputTask.h"
#include "share.h"

//-------------------------------------------------------------------------------------
/** @brief   Constructor which creates and initializes a UserInterface task object.
 *  @details This constructor creates a FreeRTOS task with the given task run function,
 *           name, priority, and stack size. Its purpose is to determine the ball position
 *           setpoint based on the UserInput sensor measurement.
 *  @param   a_name A character string which will be the name of this task
 *  @param   a_priority The priority at which this task will initially run (default: 0)
 *  @param   a_stack_size The size of this task's stack in bytes
 *                        (default: @c configMINIMAL_STACK_SIZE)
 *  @param   p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which
 *                     can be used by this task to communicate (default: NULL)
 */
UserInputTask::UserInputTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

//-------------------------------------------------------------------------------------
/** @brief   The @c run() function for the UserInterface task.
 *  @details This method is called by the RTOS scheduler. The function converts the
 *  		 linear potentiometer measurements to user position in m and user velocity
 *  		 in m/s. Shared variables are updated after the calculations are performed.
 */
void UserInputTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
	// initialize task variables to 0 upon system startup
    uint16_t adc_reading = 0;
    float user_position = 0;
    float user_velocity = 0;
    float* prev_user_position = (float*)calloc(1, sizeof(float));

	for (;;) {
		adc_reading = p_user_adc_reading -> get();	// get the linear potentiometer sensor reading
		user_position = ((float)adc_reading - 2090)/4675; // convert from ADC counts to position (m)
		user_velocity = user_position - *prev_user_position; // calculate x_dot (m/s)
		p_ball_position -> put(user_position);	// update the user_position variable
		p_ball_velocity -> put(user_velocity);	// update the user_velocity variable
		*prev_user_position = user_position;	// store current position for next loop
		delay_from_for_ms(xLastWakeTime, 100); // delay that determines the timing of the task
	}
}