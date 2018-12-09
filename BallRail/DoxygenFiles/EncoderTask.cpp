/*
 * EncoderTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "EncoderTask.h"
#include "share.h"

//-------------------------------------------------------------------------------------
/** @brief   Constructor which creates and initializes an Encoder task object.
 *  @details This constructor creates a FreeRTOS task with the given task run function,
 *           name, priority, and stack size. Its purpose is to determine the angle of
 *           the beam based on the encoder sensor measurements.
 *  @param   a_name A character string which will be the name of this task
 *  @param   a_priority The priority at which this task will initially run (default: 0)
 *  @param   a_stack_size The size of this task's stack in bytes
 *                        (default: @c configMINIMAL_STACK_SIZE)
 *  @param   p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which
 *                     can be used by this task to communicate (default: NULL)
 */
EncoderTask::EncoderTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

//-------------------------------------------------------------------------------------
/** @brief   The @c run() function for the Encoder task.
 *  @details This method is called by the RTOS scheduler. The function implements a
 *  		 modulo positioning algorithm to account for discontinuity in the
 *  		 absolute position output from the encoder sensor. The encoder counts are
 *  		 converted to angle measurements in radians and angular velocity in rad/s.
 *  		 Shared variables are updated after the calculations are performed.
 */
void EncoderTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
	// initialize task variables to 0 upon system startup
	uint16_t encoder_reading = 0;
	uint16_t prev_encoder_reading = 1000;	// modulo position feature: beam ang velocity should be close to 0
	int16_t encoder_delta = 0;
	uint8_t overflow_counter = 1;	// modulo position feature: beam starts level
	float beam_angle = 0;
	float beam_ang_velocity = 0;
	float prev_beam_angle = -0.8;	// modulo positon feature: beam ang velocity should be close to 0

	for (;;) {
		// calculate the change in encoder counts and keep track of discontinuity (modulo positioning)
		encoder_delta = p_encoder_reading -> get() - prev_encoder_reading;
		if (encoder_delta < -1500)
		{
			overflow_counter += 1;
		}
		if (encoder_delta > 1500)
		{
			overflow_counter -= 1;
		}
		if (overflow_counter <0)
		{
			p_safe -> put(false);
		}
		encoder_reading = 4096*overflow_counter + p_encoder_reading -> get() - 920; // modulo positioning calculation
		beam_angle = (float)encoder_reading*(90.76/8224)*3.14159/180 - 0.802834; // convert from encoder counts to angle (radians)
		beam_ang_velocity = beam_angle - prev_beam_angle;	// calculate ang velocity (rad/s)
		p_beam_angle -> put(beam_angle); // update beam angle variable
		p_beam_ang_velocity -> put(beam_ang_velocity);	// update beam angular velocity variable
		prev_beam_angle = beam_angle;	// store current beam angle for next loop velocity calc
		prev_encoder_reading = p_encoder_reading -> get(); // store current encoder reading for next loop encoder delta calc
		delay_from_for_ms(xLastWakeTime, 5); // delay that determines the timing of the task
	}
}
