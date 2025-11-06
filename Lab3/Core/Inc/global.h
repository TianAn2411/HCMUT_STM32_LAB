/*
 * global.h
 *
 *  Created on: Nov 5, 2025
 *      Author: Truong
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "7seg.h"
#include "state_machine.h"
#include "led_display.h"
#include "software_timer.h"
#include "button.h"
#include "main.h"

//main state
#define INIT			0
#define AUTO_STATE		1
#define MANUAL_STATE	2
#define CONFIG_STATE 	3
extern int mode;

//light state

#define NORMAL_RED 		11
#define NORMAL_YELLOW	12
#define NORMAL_GREEN 	13

#define BLINK_RED		21
#define BLINK_YELLOW	22
#define BLINK_GREEN 	23
#define BLINK_RED_GREEN		24
#define BLINK_RED_YELLOW	25
#define BLINK_GREEN_RED 	26
extern int manual_blink_mode;

//config
#define CONFIG_RED		31
#define CONFIG_GREEN	32
#define CONFIG_YELLOW	33
extern int config_mode;

//button
#define LONG_PRESSED_TIME	 200 //(200ms)
#define NORMAL_STATE	GPIO_PIN_SET
#define PRESSED_STATE	GPIO_PIN_RESET
#define MAX_BUTTON		3
extern int longPressedTime[MAX_BUTTON];
extern int button_flag[MAX_BUTTON];
extern int button_long_flag[MAX_BUTTON];
extern int keyReg0[MAX_BUTTON];
extern int keyReg1[MAX_BUTTON];
extern int keyReg2[MAX_BUTTON];
extern int keyReg3[MAX_BUTTON];

//Timer
#define MAX_TIMER 20
extern int timer_flag[MAX_TIMER];
extern int timer_counter[MAX_TIMER];

//LED and 7SEG
extern uint8_t led7seg_num_display[];
extern int led_buffer[4];
extern int led_index;
extern int red_time, green_time, yellow_time;
extern int road1_state, road2_state;
extern int road1_counter, road2_counter;
extern int counter;
#endif /* INC_GLOBAL_H_ */
