/*
 * scheduler.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Admin
 */

#include "scheduler.h"
sTasks SCH_tasks_G[SCH_MAX_TASKS];
sTasks *head_waiting_list = NULL;
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

static void delayInsert(sTasks *new_task, uint32_t DELAY){
    new_task->next = NULL;
    new_task->prev = NULL;


    if (head_waiting_list == NULL){
        new_task->Delay = DELAY;
        head_waiting_list = new_task;
        return;
    }


    if (DELAY < head_waiting_list->Delay){
        head_waiting_list->Delay -= DELAY;
        new_task->next = head_waiting_list;
        head_waiting_list->prev = new_task;
        new_task->Delay = DELAY;
        head_waiting_list = new_task;
        return;
    }


    sTasks *current_task = head_waiting_list;
    uint32_t temp_delay = DELAY;

    while (current_task->next != NULL && temp_delay >= current_task->Delay){
        temp_delay -= current_task->Delay;
        current_task = current_task->next;
    }

    if (temp_delay >= current_task->Delay && current_task->next == NULL){

        temp_delay -= current_task->Delay;
        current_task->next = new_task;
        new_task->prev = current_task;
        new_task->Delay = temp_delay;
    } else {

        new_task->Delay = temp_delay;
        current_task->Delay -= temp_delay;

        new_task->next = current_task;
        new_task->prev = current_task->prev;
        if (current_task->prev != NULL){
            current_task->prev->next = new_task;
        }
        current_task->prev = new_task;
    }
}
void SCH_Init(void) {
    // chưa có task nào
    head_waiting_list = NULL;

    // queue rỗng
    ready_head  = 0;
    ready_tail  = 0;
    ready_count = 0;

    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask  = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe  = 0;
        SCH_tasks_G[i].next = 0;
        SCH_tasks_G[i].prev = 0;
        SCH_tasks_G[i].TaskID = i;

    }
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
    int index = 0;
    // Tìm slot trống (sửa thứ tự điều kiện!)
    while ((index < SCH_MAX_TASKS) && (SCH_tasks_G[index].pTask != NULL)){
        index++;
    }
    if (index == SCH_MAX_TASKS) return;

    sTasks *new_task = &SCH_tasks_G[index];
    new_task->pTask  = pFunction;
    new_task->Period = PERIOD;
    new_task->TaskID = index;
    new_task->RunMe  = 0;

    delayInsert(new_task, DELAY);
}

void SCH_Update(void){
    if (head_waiting_list == NULL) return;

    // Giảm delay node đầu
    if (head_waiting_list->Delay > 0) {
        head_waiting_list->Delay--;
    }

    // Có thể có nhiều task cùng Delay = 0
    while (head_waiting_list != NULL && head_waiting_list->Delay == 0) {
        sTasks *task = head_waiting_list;      // lưu lại task cũ

        // bỏ khỏi list
        head_waiting_list = head_waiting_list->next;
        if (head_waiting_list != NULL) {
            head_waiting_list->prev = NULL;
        }

        task->next = NULL;
        task->prev = NULL;

        // đánh dấu ready
        task->RunMe++;
        pushQueue(task->TaskID);
    }
//     Trường hợp chỉ cập nhật 1 task khi có delay = 0
//       sTasks *task = head_waiting_list;      // lưu lại task cũ
//
//       // bỏ khỏi list
//       head_waiting_list = head_waiting_list->next;
//       if (head_waiting_list != NULL) {
//           head_waiting_list->prev = NULL;
//       }
//
//       task->next = NULL;
//       task->prev = NULL;
//
//       task->RunMe++;
//       pushQueue(task->TaskID);
}

void SCH_Dispatch_Tasks(void){
	uint32_t id;
	if (popQueue(&id)){
		SCH_tasks_G[id].RunMe--;
		(*SCH_tasks_G[id].pTask)();
		delayInsert(&SCH_tasks_G[id], SCH_tasks_G[id].Period);
	}
}

void SCH_Delete_Task(uint32_t TaskID){
	sTasks *deleted = &SCH_tasks_G[TaskID];
	if (deleted->pTask == NULL){
		return;
	}else{
	    if (deleted->next != NULL) {
	        deleted->next->Delay += deleted->Delay;
	    }
	}

	if (deleted->prev != NULL){
		deleted->prev->next = deleted->next;
	}else{
		if (head_waiting_list == deleted){
			head_waiting_list = deleted->next;
		}
	}
	if (deleted->next != NULL){
		deleted->next->prev = deleted->prev;
	}

	deleted->pTask = NULL;
	deleted->next = NULL;
	deleted->prev = NULL;
	deleted->RunMe = 0;
}

