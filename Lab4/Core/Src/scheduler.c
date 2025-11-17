/*
 * scheduler.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */


#include "scheduler.h"
sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;
//----- Queue---
static uint8_t ready_q[SCH_MAX_TASKS];
static uint8_t ready_head = 0;
static uint8_t ready_tail = 0;
static uint8_t ready_count = 0;

static void pushQueue(uint32_t id){
	if (id > SCH_MAX_TASKS){
		return;
	}
	ready_q[ready_tail] = id;
	ready_tail = (ready_tail + 1) % SCH_MAX_TASKS;
	ready_count++;
}
static int popQueue(uint32_t *id){
	if (ready_count == 0){
		return 0;
	}
	*id = ready_q[ready_head];
	ready_head = (ready_head + 1) % SCH_MAX_TASKS;
	ready_count--;
	return 1;
}
void SCH_Init(void){
	current_index_task = 0;
	ready_head = ready_tail = ready_count = 0;
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if (current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;
		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Update(void){
	for (int i = 0; i < current_index_task; i++){
		if (SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
			pushQueue(i);
		}
	}
}

void SCH_Dispatch_Tasks(void){
	uint32_t id;
	if (popQueue(&id)){
		if (SCH_tasks_G[id].RunMe > 0){
			SCH_tasks_G[id].RunMe--;
			(*SCH_tasks_G[id].pTask)();
		}
	}
}
