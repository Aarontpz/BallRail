/*
 * ControllerTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "ControllerTask.h"
#include "share.h"
#include <math.h>

ControllerTask::ControllerTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

void ControllerTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
	float Nbar = 57;
	float K1 = 48.1048;
	float K2 = 27.9486;
	float K3 = 27.8920;
	float K4 = -4.3360;
	float x = 0;
	float x_dot = 0;
	float theta = 0;
	float theta_dot = 0;
	float motor_voltage = 0;

	for (;;) {
//		theta = asin(p_beam_angle->get()); // beam angle in radians
		theta = p_beam_angle->get();
		theta_dot = p_beam_ang_velocity->get(); // beam angular velocity in rad/s
//		x = (p_beam_angle -> get())/cos(theta);	// ball position in m
		x = (p_beam_angle -> get());
		x_dot = p_ball_position -> get(); // ball velocity in m/s
		motor_voltage = Nbar*(p_set_ball_position->get()) - K1*x - K2*x_dot - K3*theta - K4*theta_dot;
//		motor_voltage = 0x00FF;
		p_motor_voltage_pwm -> put(motor_voltage);
		delay_from_for_ms(xLastWakeTime, 10); //delay for 5ms
	}
}
