/*
 * scheduler.h
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include <stddef.h>
#include <stdint.h>
typedef struct sTasks{
	void (*pTask)(void);
	uint32_t	Delay;
	uint32_t	Period;
	uint8_t		RunMe;
	uint32_t	TaskID;
	struct sTasks *next; // Trỏ tới task phía sau
	struct sTasks *prev; // Trỏ tới task phía trước
}sTasks;

#define SCH_MAX_TASKS 40
void SCH_Init(void);
void SCH_Add_Task(	void (*pFunction)(),
					uint32_t DELAY,
					uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(uint32_t TaskID);
#endif /* INC_SCHEDULER_H_ */
