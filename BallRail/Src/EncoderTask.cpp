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
	float beam_angle = 0;
	float beam_ang_velocity = 0;
	float prev_beam_angle = 0;
	HAL_StatusTypeDef result;
	/*Task LOOP code here */

	for (;;) {
//		HAL_ADC_Start(&hadc3);
//
//		if (HAL_ADC_PollForConversion(&hadc3, 1000000) == HAL_OK)
//		{
//		  adc_reading = HAL_ADC_GetValue(&hadc3);
//          sprintf(adc_buff, "**%"PRIu32"\r\n", adc_reading);
//		}
//		else //trying to debug this step...
//		{
//		  sprintf(adc_buff, "POOP IT NOT WORK\r\n");
//		}
//		HAL_UART_Transmit(&huart2, (uint8_t*)adc_buff, strlen(adc_buff), 0xFFFF);

//		GPIOC -> ODR &= ~GPIO_PIN_5;
//		result = HAL_SPI_Receive(&hspi2, spi_buff, 1, 100000);
//		if (result != HAL_OK) {
////			sprintf(adc_buff, "POOP IT NOT WORK\r\n");
//		}
//		else {
//			encoder_reading = spi_buff[0]<< 4 | (spi_buff[1] & 0xF0) >> 4;	// read the encoder serial line
			encoder_reading = p_encoder_reading -> get();
//			beam_angle = encoder_reading;
			beam_angle = 2*3.14159*(float)encoder_reading/4095; // convert from encoder counts to angle (radians)
			beam_ang_velocity = beam_angle - prev_beam_angle;
			p_beam_angle -> put(beam_angle); // update shared variable
			p_beam_ang_velocity -> put(beam_ang_velocity);
			prev_beam_angle = beam_angle;
//			sprintf(adc_buff, "SPI Received %hu%hu\r\n", spi_buff[0], spi_buff[1]);
//		}
//		GPIOC -> ODR |= GPIO_PIN_5;
//		HAL_UART_Transmit(&huart2, (uint8_t*)adc_buff, strlen(adc_buff), 0xFFFF);

		delay_from_for_ms(xLastWakeTime, 50); // delay for 1ms
	}
}
