//*************************************************************************************
/** @file    BallPositionTask.h
 *  @brief   Determines the ball position and velocity.
 *  @details This file defines the constructor and run method for the BallPosition task.
 *
 *  Revised:
 *    \li 12-08-2018 JAT Original file
 */
//*************************************************************************************

#ifndef _BALLPOSITIONTASK_H_
#define _BALLPOSITIONTASK_H_

#include "main.h"
#include "stm32l4xx_hal.h"
#include "taskbase.h"                       // The base class for all tasks
#include "taskqueue.h"                      // Queues transmit data between tasks
#include "taskshare.h"                      // Queues that only carry text
#include "emstream.h"

/** @brief   Implements a task to determine the ball position.
 *  @details This class is an extension of @c TaskBase. The purpose of the class
 *  		 is to determine the physical states of the ball.
 */
class BallPositionTask : public TaskBase {
public:
	/** @brief   Construct a BallPosition task.
	 *  @details This constructor sets up the task name, priority, stack size,
	 *  		 and serial stream.
	 *  @param   a_name A character string which will be the name of this task
	 *  @param   a_priority The priority at which this task will initially run (default: 0)
	 *  @param   a_stack_size The size of this task's stack in bytes
	 *                        (default: @c configMINIMAL_STACK_SIZE)
	 *  @param   p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which
	 *                     can be used by this task to communicate (default: NULL)
	 */
	BallPositionTask(const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev);

	/** @brief   The run method of the BallPosition task that is repeatedly called by the RTOS scheduler.
	 */
	void run(void);
};

#endif  // _BALLPOSITIONTASK_H_