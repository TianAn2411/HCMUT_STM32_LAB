/*
 * 7seg.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */
#include "global.h"

void display7SEG(int road_way, int num){
	if (road_way != 1 && road_way !=2){
		return;
	}
	if (num < 0 || num > 9){
		return;
	}
	switch (road_way){
		case 1:
			HAL_GPIO_WritePin(SEG1_1_GPIO_Port, SEG1_1_Pin, !((~led7seg_num_display[num]) & (1 << 0)));
			HAL_GPIO_WritePin(SEG1_2_GPIO_Port, SEG1_2_Pin, !((~led7seg_num_display[num]) & (1 << 1)));
			HAL_GPIO_WritePin(SEG1_3_GPIO_Port, SEG1_3_Pin, !((~led7seg_num_display[num]) & (1 << 2)));
			HAL_GPIO_WritePin(SEG1_4_GPIO_Port, SEG1_4_Pin, !((~led7seg_num_display[num]) & (1 << 3)));
			HAL_GPIO_WritePin(SEG1_5_GPIO_Port, SEG1_5_Pin, !((~led7seg_num_display[num]) & (1 << 4)));
			HAL_GPIO_WritePin(SEG1_6_GPIO_Port, SEG1_6_Pin, !((~led7seg_num_display[num]) & (1 << 5)));
			HAL_GPIO_WritePin(SEG1_7_GPIO_Port, SEG1_7_Pin, !((~led7seg_num_display[num]) & (1 << 6)));
			break;
		case 2:
			HAL_GPIO_WritePin(SEG2_1_GPIO_Port, SEG2_1_Pin, !((~led7seg_num_display[num]) & (1 << 0)));
			HAL_GPIO_WritePin(SEG2_2_GPIO_Port, SEG2_2_Pin, !((~led7seg_num_display[num]) & (1 << 1)));
			HAL_GPIO_WritePin(SEG2_3_GPIO_Port, SEG2_3_Pin, !((~led7seg_num_display[num]) & (1 << 2)));
			HAL_GPIO_WritePin(SEG2_4_GPIO_Port, SEG2_4_Pin, !((~led7seg_num_display[num]) & (1 << 3)));
			HAL_GPIO_WritePin(SEG2_5_GPIO_Port, SEG2_5_Pin, !((~led7seg_num_display[num]) & (1 << 4)));
			HAL_GPIO_WritePin(SEG2_6_GPIO_Port, SEG2_6_Pin, !((~led7seg_num_display[num]) & (1 << 5)));
			HAL_GPIO_WritePin(SEG2_7_GPIO_Port, SEG2_7_Pin, !((~led7seg_num_display[num]) & (1 << 6)));
			break;
		default:
			break;
	}
}

void update7SEG(int index){
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, GPIO_PIN_SET);
	switch(index){
		case 0:
			display7SEG(1, led_buffer[0]);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			display7SEG(1, led_buffer[1]);
//			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			display7SEG(2, led_buffer[2]);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, GPIO_PIN_SET);
			break;
		case 3:
			display7SEG(2, led_buffer[3]);
//			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}

void updateLEDBuffer(int road_way, int num){
	switch (road_way){
		case 1:
			led_buffer[0] = num / 10;
			led_buffer[1] = num % 10;
			break;
		case 2:
			led_buffer[2] = num / 10;
			led_buffer[3] = num % 10;
			break;
		default:
			break;
	}
}
