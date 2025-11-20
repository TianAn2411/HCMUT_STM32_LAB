/*
 * global.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */
#include "global.h"

int mode = INIT;
int red_time = 9, green_time = 6, yellow_time = 3;
int road1_state = NORMAL_RED, road2_state = NORMAL_GREEN;
int road1_counter, road2_counter;
int manual_blink_mode = INIT;
int config_mode = CONFIG_RED;
int counter = 0;
int led_buffer[4] = {0};
uint8_t led7seg_num_display[] = {
		/*0*/ 0x40,/*0b1000000*/
		/*1*/ 0x79,/*0b11111001*/
		/*2*/ 0x24,/*0b0100100*/
		/*3*/ 0x30,/*0b0110000*/
		/*4*/ 0x19,/*0b0011001*/
		/*5*/ 0x12,/*0b0010010*/
		/*6*/ 0x02,/*0b0000010*/
		/*7*/ 0x78,/*0b1111000*/
		/*8*/ 0x00,/*0b0000000*/
		/*9*/ 0x10/*0b0010000*/
};
int led_index = 0;
int keyReg0[MAX_BUTTON];
int keyReg1[MAX_BUTTON];
int keyReg2[MAX_BUTTON];
int keyReg3[MAX_BUTTON];
int longPressedTime[MAX_BUTTON];
int button_flag[MAX_BUTTON];
int button_long_flag[MAX_BUTTON];

int t_road1 = 0;
int t_road2 = 0;
int t_scan_led = 0;
int t_1s = 100;
int t_blink = 0;
