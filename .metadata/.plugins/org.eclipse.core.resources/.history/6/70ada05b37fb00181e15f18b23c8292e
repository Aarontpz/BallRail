/*
 * BallPositionTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "BallPositionTask.h"
#include "share.h"

BallPositionTask::BallPositionTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

void BallPositionTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
//    char adc_buff[30]; //buffer for printing out adc reading
    uint16_t adc_reading = 0;
    float ball_position = 0;
    float ball_velocity = 0;
    float* prev_ball_position = (float*)calloc(1, sizeof(float));
	/*Task LOOP code here */

	for (;;) {

//	    HAL_ADC_Start(&hadc3);
//
//		if (HAL_ADC_PollForConversion(&hadc3, 1000000) == HAL_OK)
//		{
//		  adc_reading = HAL_ADC_GetValue(&hadc3);
		  adc_reading = p_adc_reading -> get();
		  ball_position = ((float)adc_reading - 2090)/4675; // convert from ADC counts to position (m)
//		  ball_position = adc_reading;
		  ball_velocity = ball_position - *prev_ball_position; // calculate x_dot
		  p_ball_position -> put(ball_position);
		  p_ball_velocity -> put(ball_velocity);
		  *prev_ball_position = ball_position;
//          sprintf(adc_buff, "**%"PRIu32"\r\n", adc_reading);
//		}
//		else //trying to debug this step...
//		{
////		  sprintf(adc_buff, "POOP IT NOT WORK\r\n");
//		}
//		HAL_UART_Transmit(&huart2, (uint8_t*)adc_buff, strlen(adc_buff), 0xFFFF);
		delay_from_for_ms(xLastWakeTime, 20); // delay for 1ms
	}
}
