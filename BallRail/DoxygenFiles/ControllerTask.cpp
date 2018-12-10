/*
 * ControllerTask.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

#include "ControllerTask.h"
#include "share.h"
#include <math.h>

const float VS = 24.0;	// Motor supply voltage
const float Nbar = 40;	// Feed Forward gain to minimize steady state error. LQR = 57
const float K1 = 50; 	// Ball Position state gain. LQR = 48.1048  0.3224
const float K2 = 1700;	// Ball Velocity state gain. LQR = 27.9486
const float K3 = 60; 	// Beam Angle state gain. LQR = 27.8920
const float K4 = 10; 	// Beam Angular Velocity state gain. LQR = -4.3360

//-------------------------------------------------------------------------------------
/** @brief   Constructor which creates and initializes a controller task object.
 *  @details This constructor creates a FreeRTOS task with the given task run function,
 *           name, priority, and stack size. Its purpose is to implement the state space
 *           control algorithm with established gains.
 *  @param   a_name A character string which will be the name of this task
 *  @param   a_priority The priority at which this task will initially run (default: 0)
 *  @param   a_stack_size The size of this task's stack in bytes
 *                        (default: @c configMINIMAL_STACK_SIZE)
 *  @param   p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which
 *                     can be used by this task to communicate (default: NULL)
 */
ControllerTask::ControllerTask (const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
}

//-------------------------------------------------------------------------------------
/** @brief   The @c run() function for the Controller task.
 *  @details This method is called by the RTOS scheduler. The function reads the system
 *  		 system states and establishes the required PWM signal to send to the motor.
 *  		 NOTE: The control algorithm is FULL STATE FEEDBACK
 */
void ControllerTask::run(void) {
	static TickType_t xLastWakeTime = xTaskGetTickCount ();
	// initialize controller variables to 0 upon system startup
	float x = 0;
	float x_dot = 0;
	float theta = 0;
	float theta_dot = 0;
	float motor_voltage = 0;

	for (;;) {
		theta = p_beam_angle->get();	// beam angle in rad
		theta_dot = p_beam_ang_velocity->get(); // beam angular velocity in rad/s
		x = p_ball_position -> get();	// ball position in m
		x_dot = p_ball_velocity -> get(); // ball velocity in m/s
		motor_voltage = (Nbar*(p_set_ball_position->get()) - K1*x - K2*x_dot - K3*theta - K4*theta_dot)/VS;	// calculate the motor duty cycle
		p_motor_voltage_pwm -> put(motor_voltage);	// update the motor duty cycle
		delay_from_for_ms(xLastWakeTime, 10); // delay that determines the timing of the task
	}
}