/*
 * uart_communication.c
 *
 *  Created on: Dec 4, 2025
 *      Author: Admin
 */
#include "global.h"
#include <stdio.h>

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
int counter = 0;


uint32_t adc_value = 0;
char str_buffer[50];
uint32_t timer_timeout = 0;

void uart_communication_fsm() {
	switch (status_uart) {
		case COMM_WAIT_RST:
			if (command_flag) {
				command_flag = 0;

				if (strcmp((char*)command_data, "RST") == 0) {
					adc_value = HAL_ADC_GetValue(&hadc1);
					status_uart = COMM_SEND_ADC;
				}
			}

			break;
		case COMM_SEND_ADC:
			sprintf(str_buffer, "\n!ADC=%d#\r\n", (int)adc_value);
			HAL_UART_Transmit(&huart2, (uint8_t*)str_buffer, strlen(str_buffer), 100);

			timer_timeout = HAL_GetTick();
			status_uart = COMM_WAIT_OK;

			break;
		case COMM_WAIT_OK:
			if (command_flag) {
				command_flag = 0;

				if (strcmp((char*)command_data, "OK") == 0) {
					status_uart = COMM_WAIT_RST;
				}
			} else if (HAL_GetTick() - timer_timeout >= 3000) {	//time out
				status_uart = COMM_SEND_ADC;
			}

			break;
		default:
			status_uart = COMM_WAIT_RST;

			break;
	}
}
