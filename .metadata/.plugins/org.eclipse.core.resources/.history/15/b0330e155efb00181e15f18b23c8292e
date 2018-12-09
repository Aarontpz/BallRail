//TODO: #ifndef protections lol
#include "main.h"
#include "stm32l4xx_hal.h"
#include "taskbase.h"                       // The base class for all tasks
#include "taskqueue.h"                      // Queues transmit data between tasks
#include "taskshare.h"                      // Queues that only carry text
#include "emstream.h"

//extern TaskShare<bool>* p_safe; // Declare as extern in task .h files

class MotorDriveTask : public TaskBase {
public:
	MotorDriveTask(const char* a_name,
			unsigned portBASE_TYPE a_priority,
			size_t a_stack_size,
			emstream* p_ser_dev);
	void run(void);

};
