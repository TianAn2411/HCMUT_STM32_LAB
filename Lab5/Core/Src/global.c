/*
 * global.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */
#include "global.h"

// --- Biến cho bộ đệm UART ---
uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

// --- Biến cho Command Parser ---
uint8_t command_flag = 0;
uint8_t command_data[MAX_BUFFER_SIZE];
uint8_t idx_data = 0;

// --- Biến trạng thái cho FSM Giao tiếp ---
// Khởi đầu là trạng thái chờ lệnh RST
uint8_t status_uart = COMM_WAIT_RST;

// --- Biến cho ADC (nếu muốn lưu toàn cục) ---
uint32_t ADC_value = 0;
