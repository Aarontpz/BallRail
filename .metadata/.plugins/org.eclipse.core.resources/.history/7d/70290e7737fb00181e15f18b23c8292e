/*
 * EncoderTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "EncoderTask.h"
#include "share.h"

EncoderTask::EncoderTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

void EncoderTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
//	char adc_buff[30]; //buffer for printing out adc reading
	uint8_t spi_buff[3];
	spi_buff[2] = '\0';
	uint16_t encoder_reading = 0;
	uint16_t prev_encoder_reading = 1000;
	int16_t encoder_delta = 0;
	uint8_t overflow_counter = 1;
	float beam_angle = 0;
	float beam_ang_velocity = 0;
	float prev_beam_angle = -0.8;
	HAL_StatusTypeDef result;
	/*Task LOOP code here */

	for (;;) {

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

		encoder_reading = 4096*overflow_counter + p_encoder_reading -> get() - 920;

//		beam_angle = encoder_reading;
		beam_angle = (float)encoder_reading*(90.76/8224)*3.14159/180 - 0.802834; // convert from encoder counts to angle (radians)
		beam_ang_velocity = beam_angle - prev_beam_angle;
		p_beam_angle -> put(beam_angle); // update shared variable
		p_beam_ang_velocity -> put(beam_ang_velocity);
		prev_beam_angle = beam_angle;
		prev_encoder_reading = p_encoder_reading -> get();

		delay_from_for_ms(xLastWakeTime, 5); // delay for 1ms
	}
}
