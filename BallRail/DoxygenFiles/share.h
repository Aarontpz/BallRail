/*
 * share.h
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */

//-------------------------------------------------------------------------------------
/** @brief   Shared variable declarations for the RTOS system.
 *  @details This file contains the external declarations of the shared variable pointers.
 * 			 Shared variables are accessible to the tasks by dereferencing the pointer.
 *  @param   p_safe Indicates if the beam or ball is within safe operating range.
 *  @param   p_ball_position Ball position measurement.
 *  @param   p_ball_velocity Ball velocity measurement.
 *  @param   p_beam_angle Beam angle measurement.
 *  @param   p_beam_ang_velocity Beam angular velocity measurement.
 *  @param   p_motor_voltage_pwm Motor voltage command duty cycle (signed for directionality).
 *  @param   p_set_ball_position Desired ball position set point to the controller.
 *  @param   p_adc_reading Raw ball position sensor output (linear potentiometer).
 *  @param   p_encoder_reading Raw beam angle sensor output (encoder).
 *  @param   p_user_adc_reading Raw user-desired ball position sensor output (linear potentiometer).
 */
extern TaskShare<bool>* p_safe;
extern TaskShare<float>* p_ball_position;
extern TaskShare<float>* p_ball_velocity;
extern TaskShare<float>* p_beam_angle;
extern TaskShare<float>* p_beam_ang_velocity;
extern TaskShare<float>* p_motor_voltage_pwm;
extern TaskShare<float>* p_set_ball_position;
extern TaskShare<uint16_t>* p_adc_reading;
extern TaskShare<uint16_t>* p_encoder_reading;
extern TaskShare<uint16_t>* p_user_adc_reading;
