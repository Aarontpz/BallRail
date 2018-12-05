/*
 * UserInputTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "UserInputTask.h"
#include "share.h"

UserInputTask::UserInputTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

void UserInputTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
//    char adc_buff[30]; //buffer for printing out adc reading
    uint32_t adc_reading = 0;
    float set_ball_position = 0;
	/*Task LOOP code here */

	for (;;) {

//	    HAL_ADC_Start(&hadc3);
//
//		if (HAL_ADC_PollForConversion(&hadc3, 1000000) == HAL_OK)
//		{
//		  adc_reading = HAL_ADC_GetValue(&hadc3);
//		  set_ball_position = adc_reading/5000; // convert from ADC counts to position (m)
//		  p_ball_position -> put(set_ball_position);
////          sprintf(adc_buff, "**%"PRIu32"\r\n", adc_reading);
//		}
//		else //trying to debug this step...
//		{
////		  sprintf(adc_buff, "POOP IT NOT WORK\r\n");
//		}
//		HAL_UART_Transmit(&huart2, (uint8_t*)adc_buff, strlen(adc_buff), 0xFFFF);
		delay_from_for_ms(xLastWakeTime, 1); // delay for 1ms
	}
}
