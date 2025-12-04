/*
 * global.h
 *
 *  Created on: Nov 5, 2025
 *      Author: Truong
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "command_parser.h"
#include "uart_communication.h"
#include "software_timer.h"
#include "scheduler.h"
#include <string.h>
// Định nghĩa trạng thái & lệnh
#define COMM_WAIT_RST  0
#define COMM_SEND_ADC  1
#define COMM_WAIT_OK   11
#define COMM_IDLE 111

#define INIT_PARSE 4
#define WAIT_PARSE 5

#define CMD_RST 10
#define CMD_OK  2
#define CMD_NONE 3

// Khai báo biến toàn cục
#define MAX_BUFFER_SIZE 30
extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t state;
extern uint8_t command_flag;
extern uint8_t command_data[MAX_BUFFER_SIZE];
extern uint8_t idx_data;
extern uint8_t status_uart;
#define MAX_TIMER 30
#endif /* INC_GLOBAL_H_ */
