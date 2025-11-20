/*
 * software_timer.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */

#include "global.h"
//int timer_flag[MAX_TIMER];
//int timer_counter[MAX_TIMER];
//
//void setTimer(int timer_id, int dur){
//	if (timer_id < 0 || timer_id >= MAX_TIMER){
//		return;
//	}
//	timer_counter[timer_id] = dur;
//	timer_flag[timer_id] = 0;
//}
//
//int isExpired(int timer_id){
//	if (timer_flag[timer_id] == 1){
//		timer_flag[timer_id] = 0;
//		return 1;
//	}
//	return 0;
//}
//
//void timerRun(){
//	for (int i = 0; i < MAX_TIMER; i++){
//		if (timer_counter[i] > 0){
//			timer_counter[i]--;
//		}
//		if (timer_counter[i] == 0){
//			timer_flag[i] = 1;
//		}
//	}
//}
void timeCounter(){
	if (t_road1 > 0){
		t_road1--;
	}
	if (t_road2 > 0){
		t_road2--;
	}
	if (t_scan_led > 0){
		t_scan_led--;
	}
	if (t_1s > 0){
		t_1s--;
	}
	if (t_blink > 0){
		t_blink--;
	}
}
