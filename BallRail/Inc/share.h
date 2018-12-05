/*
 * share.h
 *
 *  Created on: Dec 3, 2018
 *      Author: aaron
 */


extern TaskShare<bool>* p_safe; // Declare as extern in task .h files
extern TaskShare<float>* p_ball_position;
extern TaskShare<float>* p_ball_velocity;
extern TaskShare<float>* p_beam_angle;
extern TaskShare<float>* p_beam_ang_velocity;
extern TaskShare<float>* p_motor_voltage_pwm;
extern TaskShare<float>* p_set_ball_position;
extern TaskShare<uint16_t>* p_adc_reading;
extern TaskShare<uint16_t>* p_encoder_reading;
