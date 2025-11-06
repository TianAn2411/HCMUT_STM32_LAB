/*
 * led_display.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */

#include "global.h"
int one_sec_tick = 0;

void updateTrafficLight(int state) {
	if (mode == AUTO_STATE){
		switch (road1_state){
			case NORMAL_RED:
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, GPIO_PIN_SET);
				break;
			case NORMAL_GREEN:
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, GPIO_PIN_SET);
				break;
			case NORMAL_YELLOW:
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, GPIO_PIN_RESET);
				break;
			default:
				break;
		}

		switch (road2_state){
			case NORMAL_RED:
				HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, GPIO_PIN_SET);
				break;
			case NORMAL_GREEN:
				HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, GPIO_PIN_SET);
				break;
			case NORMAL_YELLOW:
				HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, GPIO_PIN_RESET);
				break;
			default:
				break;
		}
	}else if (mode == MANUAL_STATE || (mode == CONFIG_STATE)){
		switch (state){
			case INIT:
				HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
				HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
				HAL_GPIO_TogglePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin);
				HAL_GPIO_TogglePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin);				HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
				HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
				HAL_GPIO_TogglePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin);
				break;
			case BLINK_RED_GREEN:
				clearLED();
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_RESET);
				break;
			case BLINK_RED_YELLOW:
				clearLED();
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, GPIO_PIN_RESET);
				break;
			case BLINK_GREEN_RED:
				clearLED();
				HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, GPIO_PIN_RESET);
				break;
			case BLINK_RED:
				HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
				HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
				break;
			case BLINK_YELLOW:
				HAL_GPIO_TogglePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin);
				HAL_GPIO_TogglePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin);
				break;
			case BLINK_GREEN:
				HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
				HAL_GPIO_TogglePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin);
				break;
			default:
				break;
		}
	}
}
void displayAutoTrafficLight(){
	updateTrafficLight(0);
	switch (road1_state){
		case NORMAL_RED:
			updateLEDBuffer(1, road1_counter);
			if (isExpired(0) == 1){
				road1_state = NORMAL_GREEN;
				setTimer(0, green_time * 100);
				road1_counter = green_time;
				updateLEDBuffer(1, road1_counter);
			}
			break;
		case NORMAL_GREEN:
			updateLEDBuffer(1, road1_counter);
			if (isExpired(0) == 1){
				road1_state = NORMAL_YELLOW;
				setTimer(0, yellow_time * 100);
				road1_counter = yellow_time;
				updateLEDBuffer(1, road1_counter);
			}
			break;
		case NORMAL_YELLOW:
			updateLEDBuffer(1, road1_counter);
			if (isExpired(0) == 1){
				road1_state = NORMAL_RED;
				setTimer(0, red_time * 100);
				road1_counter = red_time;
				updateLEDBuffer(1, road1_counter);
			}
			break;
		default:
			break;
	}
	switch (road2_state){
		case NORMAL_RED:
			updateLEDBuffer(2, road2_counter);
			if (isExpired(1) == 1){
				road2_state = NORMAL_GREEN;
				setTimer(1, green_time * 100);
				road2_counter = green_time;
				updateLEDBuffer(2, road2_counter);
			}
			break;
		case NORMAL_GREEN:
			updateLEDBuffer(2, road2_counter);
			if (isExpired(1) == 1){
				road2_state = NORMAL_YELLOW;
				setTimer(1, yellow_time * 100);
				road2_counter = yellow_time;
				updateLEDBuffer(2, road2_counter);
			}
			break;
		case NORMAL_YELLOW:
			updateLEDBuffer(2, road2_counter);
			if (isExpired(1) == 1){
				road2_state = NORMAL_RED;
				setTimer(1, red_time * 100);
				road2_counter = red_time;
				updateLEDBuffer(2, road2_counter);
			}
			break;
		default:
			break;
	}
}

void updateCounter(){
	if (isExpired(3) == 1){ // Timer 3 là timer 1 giây
		setTimer(3, 100);
		road1_counter--;
		road2_counter--;

		one_sec_tick = 1;
	}
	if(one_sec_tick == 1){
		one_sec_tick = 0;
		updateLEDBuffer(1, road1_counter);
		updateLEDBuffer(2, road2_counter);
	}
}
void displayTime(){
	updateCounter();
	if (isExpired(2) == 1){
		setTimer(2, 10);
		update7SEG(led_index);
		led_index = led_index + 1;
		if (led_index > 3){
			led_index = 0;
		}
	}
}
void clearLED(){
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, GPIO_PIN_SET);
}

void clear7SEG(){
	updateLEDBuffer(1, 0);
	updateLEDBuffer(2, 0);
}

void displayBlinkTrafficLight(int state){
	switch (state){
		case BLINK_RED_GREEN:
			if (isExpired(5)){
				setTimer(5,500);
				updateTrafficLight(BLINK_RED_GREEN);
			}
			break;
		case BLINK_RED_YELLOW:
			if (isExpired(5)){
				setTimer(5,200);
				updateTrafficLight(BLINK_RED_YELLOW);
			}
			break;
		case INIT:
			if (isExpired(5)){
				setTimer(5,25);
				updateTrafficLight(INIT);
			}
			break;
		case BLINK_GREEN_RED:
			if (isExpired(5)){
				setTimer(5,500);
				updateTrafficLight(BLINK_GREEN_RED);
			}
			break;
		case BLINK_RED:
			if (isExpired(5)){
				setTimer(5,50);
				updateTrafficLight(BLINK_RED);
			}
			break;
		case BLINK_GREEN:
			if (isExpired(5)){
				setTimer(5,50);
				updateTrafficLight(BLINK_GREEN);
			}
			break;
		case BLINK_YELLOW:
			if (isExpired(5)){
				setTimer(5,50);
				updateTrafficLight(BLINK_YELLOW);
			}
			break;
		default:
			break;
	}

}
