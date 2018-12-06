/*
 * ControllerTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "ControllerTask.h"
#include "share.h"
#include <math.h>

//#define VS 24.0
//#define Nbar 10	// 57
//#define K1 0.3224 // 48.1048
//#define K2 15.16 // 27.9486
//#define K3 64.5 // 27.8920
//#define K4 0.13 // -4.3360
const float VS = 24.0;
const float Nbar = 11;	// 57
const float K1 = 10; // 48.1048  0.3224
const float K2 = 15.16;// 27.9486
const float K3 = 64.5; // 27.8920
const float K4 = 0.13; // -4.3360

ControllerTask::ControllerTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

void ControllerTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
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
		x = p_ball_position -> get();
		x_dot = p_ball_velocity -> get(); // ball velocity in m/s
		motor_voltage = (Nbar*(p_set_ball_position->get()) - K1*x - K2*x_dot - K3*theta - K4*theta_dot)/VS;
//		motor_voltage = 0x00FF;
		p_motor_voltage_pwm -> put(motor_voltage);
		delay_from_for_ms(xLastWakeTime, 10); //delay for 5ms
	}
}
