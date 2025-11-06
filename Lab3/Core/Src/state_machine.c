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
			setTimer(0, red_time * 100);
			setTimer(1, green_time * 100);
			setTimer(2, 10);
			setTimer(3, 100);
			setTimer(5,50);
			road1_counter = red_time;
			road2_counter = green_time;
			break;
		case AUTO_STATE:
			displayAutoTrafficLight(0);
			displayTime();
			if(isButtonPressed(0)){
				mode = MANUAL_STATE;
				manual_blink_mode = BLINK_RED_GREEN;
				updateLEDBuffer(2, 2);
				setTimer(2, 25);
				setTimer(5, 50);
				clear7SEG();
				clearLED();
				break;
			}
			break;
		case MANUAL_STATE:
			switch (manual_blink_mode){
				case BLINK_RED_GREEN:
					if (manual_blink_mode != BLINK_RED_GREEN){
						manual_blink_mode = BLINK_RED_GREEN;
					}
					if(isButtonPressed(1)){
						manual_blink_mode = BLINK_RED_YELLOW;
//						setTimer(5, 20);
//						setTimer(2,10);
						updateLEDBuffer(2,2);
						break;
					}
//					if(isExpired(5)){
//						setTimer(5, 500);
//						updateTrafficLight(manual_blink_mode);
//					}
					if(isExpired(2)){
						setTimer(2,10);
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}
					}
//					displayBlinkTrafficLight(manual_blink_mode);
					break;
				case BLINK_RED_YELLOW:
					if (manual_blink_mode != BLINK_RED_YELLOW){
						manual_blink_mode = BLINK_RED_YELLOW;
					}
					if(isExpired(5)){
						if(manual_blink_mode != BLINK_GREEN_RED){
							manual_blink_mode = BLINK_GREEN_RED;
							break;
						}
//						setTimer(5, 500);
//						setTimer(2,10);
						updateLEDBuffer(2,2);
					}
					if(isExpired(2)){
						setTimer(2,10);
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
					if(isButtonPressed(1)){
						if(manual_blink_mode != BLINK_RED_GREEN){
							manual_blink_mode = BLINK_RED_GREEN;
						}
//						setTimer(5, 500);
//						setTimer(2,10);
						updateLEDBuffer(2,2);
						break;
					}
					if(isExpired(2)){
						setTimer(2,10);
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}
					}
					break;

			}
			if (isButtonPressed(0)){
				mode = CONFIG_STATE;
				config_mode = CONFIG_RED;
				manual_blink_mode = BLINK_RED;
				setTimer(2, 10);
				setTimer(5, 50);
				clearLED();
				temp_duration = red_time;
				updateLEDBuffer(1, temp_duration);
				updateLEDBuffer(2, 3);
				break;
			}
			displayBlinkTrafficLight(manual_blink_mode);

			if(isExpired(2)){
				setTimer(2,10);
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
//					if (isButtonPressed(2)){
//						temp_duration--;
//						if (temp_duration < 0){
//							temp_duration = 99;
//						}
//						updateLEDBuffer(1, temp_duration);
//					}
					if (isExpired(2)){
						setTimer(2, 10);
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}

					}
					if (isButtonPressed(2)){
						red_time = temp_duration;
						temp_duration = green_time;
//						setTimer(2, 10);
//						setTimer(5, 50);
//						clearLED();
//						updateLEDBuffer(1, temp_duration);
						break;
					}
					if (isButtonPressed(0)){
						config_mode = CONFIG_GREEN;
						manual_blink_mode = BLINK_GREEN;
						setTimer(2, 10);
						setTimer(5, 50);
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
//					if (isButtonPressed(2)){
//						temp_duration = temp_duration - 1;
//						if (temp_duration < 0){
//							temp_duration = 99;
//						}
//						updateLEDBuffer(1, temp_duration);
//					}
					if (isExpired(2)){
						setTimer(2, 10);
						update7SEG(led_index++);
						if (led_index > 3){
							led_index = 0;
						}

					}
					if (isButtonPressed(2)){
						green_time = temp_duration;
//						config_mode = CONFIG_YELLOW;
//						temp_duration = yellow_time;
//						manual_blink_mode = BLINK_YELLOW;
//						setTimer(2, 10);
//						setTimer(5, 50);
//						clearLED();
						updateLEDBuffer(1, temp_duration);
						updateLEDBuffer(2, 3);
						break;
					}
					if (isButtonPressed(0)){
						config_mode = CONFIG_YELLOW;
						temp_duration = yellow_time;
						manual_blink_mode = BLINK_YELLOW;
						setTimer(2, 10);
						setTimer(5, 50);
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
					if (isExpired(2)){
						setTimer(2, 10);
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
						setTimer(0, red_time * 100);
						setTimer(1, green_time * 100);
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
