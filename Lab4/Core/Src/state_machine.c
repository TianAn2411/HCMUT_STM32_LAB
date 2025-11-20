/*
 * state_machine.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */

#include "global.h"
int temp_duration;
void fsm_run(){
//	updateCounter();
	switch (mode){
		case INIT:
			clearLED();
			mode = AUTO_STATE;
//			setTimer(0, red_time * 100);
			t_road1 = red_time * 100;
//			setTimer(1, green_time * 100);
			t_road2 = green_time * 100;
//			setTimer(2, 10);
			t_scan_led = 10;
//			setTimer(3, 100);
			t_1s = 100;
//			setTimer(5,50);
			t_blink = 50;
			road1_counter = red_time;
			road2_counter = green_time;
			break;
		case AUTO_STATE:
			displayAutoTrafficLight(0);
			displayTime();
			if(isButtonPressed(0)){
				mode = MANUAL_STATE;
				manual_blink_mode = BLINK_RED_GREEN;
				t_blink = 500;
//				setTimer(2, 25);
				t_scan_led = 25;
//				setTimer(5, 50);
				t_blink = 5;
				clear7SEG();
				clearLED();
				updateLEDBuffer(2, 2);
				break;
			}
			break;
		case MANUAL_STATE:
			switch (manual_blink_mode){
				case BLINK_RED_GREEN:
					if (manual_blink_mode != BLINK_RED_GREEN){
						manual_blink_mode = BLINK_RED_GREEN;
					}
//					displayBlinkTrafficLight(manual_blink_mode);
					if(isButtonPressed(1)){
						manual_blink_mode = BLINK_RED_YELLOW;
						updateLEDBuffer(1,1);
						t_blink = 300;
						break;
					}
					if(t_scan_led == 0){
						t_scan_led = 10;
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}
					}
					break;
				case BLINK_RED_YELLOW:
					if(t_blink <= 0){
						manual_blink_mode = BLINK_GREEN_RED;
						t_blink  = 500;
						updateLEDBuffer(1,2);
						break;
					}
//					displayBlinkTrafficLight(manual_blink_mode);
					if(t_scan_led == 0){
						t_scan_led = 10;
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}
					}
					break;
				case BLINK_GREEN_RED:
					if (manual_blink_mode != BLINK_GREEN_RED){
						manual_blink_mode = BLINK_GREEN_RED;
					}
//					displayBlinkTrafficLight(manual_blink_mode);
					if(isButtonPressed(1)){
						manual_blink_mode = BLINK_YELLOW_RED;
						t_blink = 300;
						updateLEDBuffer(1,3);

						break;
					}
					if(t_scan_led == 0){
						t_scan_led = 10;
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}
					}
					break;
				case BLINK_YELLOW_RED:
					if(t_blink <= 0){
						manual_blink_mode = BLINK_RED_GREEN;
						t_blink  = 500;
						updateLEDBuffer(1,2);
						break;
					}
//					displayBlinkTrafficLight(manual_blink_mode);
					if(t_scan_led == 0){
						t_scan_led = 10;
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}
					}
					break;
				default:
					break;

			}
			displayBlinkTrafficLight(manual_blink_mode);
			if (isButtonPressed(0)){
				mode = CONFIG_STATE;
				config_mode = CONFIG_RED;
				manual_blink_mode = BLINK_RED;
//				setTimer(2, 10);
				t_scan_led = 10;
//				setTimer(5, 50);
				t_blink = 50;
				clearLED();
				temp_duration = red_time;
				updateLEDBuffer(1, temp_duration);
				updateLEDBuffer(2, 3);
				break;
			}


			if(t_scan_led == 0){
				t_scan_led = 10;
				update7SEG(led_index++);
				if (led_index > 3){
					led_index = 0;
				}
			}
			break;
		case CONFIG_STATE:{
			switch (config_mode){
				case CONFIG_RED:
					if (manual_blink_mode != BLINK_RED){
						manual_blink_mode = BLINK_RED;
						clearLED();
					}
					displayBlinkTrafficLight(manual_blink_mode);
					if (isButtonPressed(1)){
						temp_duration++;
						if (temp_duration > 99){
							temp_duration = 0;
						}
						updateLEDBuffer(1, temp_duration);
					}
					if (t_scan_led == 0){
						t_scan_led = 10;
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}

					}
					if (isButtonPressed(2)){
						red_time = temp_duration;
						break;
					}
					if (isButtonPressed(0)){
						config_mode = CONFIG_GREEN;
						manual_blink_mode = BLINK_GREEN;
						temp_duration = green_time;
//						setTimer(2, 10);
						t_scan_led = 10;
//						setTimer(5, 50);
						t_blink = 50;
						clearLED();
						updateLEDBuffer(1, temp_duration);
						updateLEDBuffer(2, 3);
						break;
					}
					break;
				case CONFIG_GREEN:
					if (manual_blink_mode != BLINK_GREEN){
						manual_blink_mode = BLINK_GREEN;
						clearLED();
					}
					displayBlinkTrafficLight(manual_blink_mode);
					if (isButtonPressed(1)){
						temp_duration++;
						if (temp_duration > 99){
							temp_duration = 0;
						}
						updateLEDBuffer(1, temp_duration);
					}
					if (t_scan_led == 0){
//						setTimer(2, 10);
						t_scan_led = 10;
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}

					}
					if (isButtonPressed(2)){
						green_time = temp_duration;
						updateLEDBuffer(1, temp_duration);
						updateLEDBuffer(2, 3);
						break;
					}
					if (isButtonPressed(0)){
						config_mode = CONFIG_YELLOW;
						temp_duration = yellow_time;
						manual_blink_mode = BLINK_YELLOW;
//						setTimer(2, 10);
						t_scan_led = 10;
//						setTimer(5, 50);
						t_blink = 50;
						clearLED();
						updateLEDBuffer(1, temp_duration);
						break;
					}
					break;
				case CONFIG_YELLOW:
					if (manual_blink_mode != BLINK_YELLOW){
						manual_blink_mode = BLINK_YELLOW;
						clearLED();
					}
					displayBlinkTrafficLight(manual_blink_mode);
					if (isButtonPressed(1)){
						temp_duration++;
						if (temp_duration > 99){
							temp_duration = 0;
						}
						updateLEDBuffer(1, temp_duration);
					}
					if (t_scan_led == 0){
//						setTimer(2, 10);
						t_scan_led = 10;
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}

					}
					if (isButtonPressed(2)){
						yellow_time = temp_duration;
//						mode = AUTO_STATE;
//						road1_counter = red_time;
//						road2_counter = green_time;
//						road1_state = NORMAL_RED;
//						road2_state = NORMAL_GREEN;
//						setTimer(0, red_time * 100);
//						setTimer(1, green_time * 100);
//						updateTrafficLight(0);
						break;
//						updateLEDBuffer(1, temp_duration);
					}
					if (isButtonPressed(0)){
						mode = AUTO_STATE;
						road1_counter = red_time;
						road2_counter = green_time;
						road1_state = NORMAL_RED;
						road2_state = NORMAL_GREEN;
//						setTimer(0, red_time * 100);
						t_road1 = red_time * 100;
//						setTimer(1, green_time * 100);
						t_road2 = green_time * 100;
						updateTrafficLight(0);
						break;
//						updateLEDBuffer(1, temp_duration);
					}
					break;
				default:
					break;
			}
			break;
		}
		default:
			break;

	}
}
