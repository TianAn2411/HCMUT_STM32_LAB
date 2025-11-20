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
/*------ DELTA LIST ------*/
static int8_t dl_head = -1;                // -1 nghĩa là rỗng
static int8_t dl_next[SCH_MAX_TASKS];      // mảng chứa task tiếp theo của task hiện tại
// Hàm add vào delay list (delay tuyệt đối)
static void delayInsert(uint8_t id, uint32_t delay) {

    int8_t cur  = dl_head;
    int8_t prev = -1;

    while (cur != -1 && delay >= SCH_tasks_G[cur].Delay) {
        delay -= SCH_tasks_G[cur].Delay;
        prev  = cur;
        cur   = dl_next[cur];
    }

    /* set delay cho task */
    SCH_tasks_G[id].Delay = delay;
    dl_next[id] = cur;

    if (prev == -1) {
        /* chèn vào đầu list */
        dl_head = id;
    } else {
        dl_next[prev] = id;
    }

    /* nếu phía sau còn node, giảm delay của nó đi phần mình vừa lấy */
    if (cur != -1) {
        SCH_tasks_G[cur].Delay -= delay;
    }
}
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
void SCH_Init(void) {
    // chưa có task nào
    current_index_task = 0;

    // queue rỗng
    ready_head  = 0;
    ready_tail  = 0;
    ready_count = 0;

    // delay list rỗng
    dl_head = -1;

    // reset toàn bộ mảng task + next
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask  = 0;
        SCH_tasks_G[i].Delay  = 0;      // delay ban đầu
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe  = 0;
        SCH_tasks_G[i].TaskID = i;

        dl_next[i] = -1;               // chưa nối với ai cả
    }
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if (current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		delayInsert(current_index_task, DELAY);
		SCH_tasks_G[current_index_task].RunMe = 0;
		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		dl_next[current_index_task]= -1;
		current_index_task++;


	}
}

//void SCH_Update(void){
//	for (int i = 0; i < current_index_task; i++){
//		if (SCH_tasks_G[i].Delay > 0){
//			SCH_tasks_G[i].Delay--;
//		}else{
//			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
//			SCH_tasks_G[i].RunMe += 1;
//			pushQueue(i);
//		}
//	}
//}
void SCH_Update(void) {
    /* nếu không có task nào thì thôi */
    if (dl_head == -1) return;

    uint8_t head = dl_head;

    /* 1. Giảm delay của task đầu list */
    if (SCH_tasks_G[head].Delay > 0) {
        SCH_tasks_G[head].Delay--;
        return;
    }
    while (dl_head != -1 && SCH_tasks_G[dl_head].Delay == 0) {
        uint8_t id = dl_head;
        dl_head     = dl_next[id];
        dl_next[id] = -1;
        SCH_tasks_G[id].RunMe += 1;
        pushQueue(id);
    }
//    if (SCH_tasks_G[dl_head].Delay == 0) {
//            uint8_t id = dl_head;
//            dl_head     = dl_next[id];
//            dl_next[id] = -1;
//            SCH_tasks_G[id].RunMe += 1;
//            pushQueue(id);
//    }
}
void SCH_Dispatch_Tasks(void){
	uint32_t id;
	if (popQueue(&id)){
//		if (SCH_tasks_G[id].RunMe > 0){
			SCH_tasks_G[id].RunMe--;
			(*SCH_tasks_G[id].pTask)();
			delayInsert(id, SCH_tasks_G[id].Period);
//		}
	}
}
