/*
 * BallPositionTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "BallPositionTask.h"
#include "share.h"

//-------------------------------------------------------------------------------------
/** @brief   Constructor which creates and initializes a BallPosition task object.
 *  @details This constructor creates a FreeRTOS task with the given task run function,
 *           name, priority, and stack size. Its purpose is to determine the ball position
 *           and velocity from the sensor measurements and update the appropriate
 *           shared variables.
 *  @param   a_name A character string which will be the name of this task
 *  @param   a_priority The priority at which this task will initially run (default: 0)
 *  @param   a_stack_size The size of this task's stack in bytes
 *                        (default: @c configMINIMAL_STACK_SIZE)
 *  @param   p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which
 *                     can be used by this task to communicate (default: NULL)
 */
BallPositionTask::BallPositionTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

//-------------------------------------------------------------------------------------
/** @brief   The @c run() function for the BallPosition task.
 *  @details This method is called by the RTOS scheduler. The function converts the
 *  		 linear potentiometer measurements to ball position in m and ball velocity
 *  		 in m/s. Shared variables are updated after the calculations are performed.
 */
void BallPositionTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
	// initialize task variables to 0 upon system startup
    uint16_t adc_reading = 0;
    float ball_position = 0;
    float ball_velocity = 0;
    float* prev_ball_position = (float*)calloc(1, sizeof(float));

	for (;;) {
		adc_reading = p_adc_reading -> get();	// get the linear potentiometer sensor reading
		ball_position = ((float)adc_reading - 2090)/4675; // convert from ADC counts to position (m)
		ball_velocity = ball_position - *prev_ball_position; // calculate x_dot (m/s)
		p_ball_position -> put(ball_position);	// update the ball_position variable
		p_ball_velocity -> put(ball_velocity);	// update the ball_velocity variable
		*prev_ball_position = ball_position;		// store current position for next loop
		delay_from_for_ms(xLastWakeTime, 20); // delay that determines the timing of the task
	}
}