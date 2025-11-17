/*
 * button.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */
#include "button.h"

#define LONG_PRESSED_TIME	 200 //(200ms)

GPIO_TypeDef* BUTTON_PORT[MAX_BUTTON] = {BUTTON1_GPIO_Port, BUTTON2_GPIO_Port, BUTTON3_GPIO_Port};
uint16_t BUTTON_PIN[MAX_BUTTON] = {BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin};


void subKeyProcess(int index){
	button_flag[index] = 1;
}

int isButtonPressed(int index){
	if (button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}else{
		return 0;
	}
}

int isButtonLongPressed(int index){
	if (button_long_flag[index] == 1){
		button_long_flag[index] = 0;
		return 1;
	}else{
		return 0;
	}
}

void getKeyInput(){
	for (int i = 0; i < MAX_BUTTON; i++){
		keyReg2[i] = keyReg1[i];
		keyReg1[i] = keyReg0[i];
		keyReg0[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);
		if ((keyReg0[i] == keyReg1[i]) && (keyReg1[i] == keyReg2[i])){
			if (keyReg3[i] != keyReg2[i]){
				keyReg3[i] = keyReg2[i];
				if(keyReg3[i] == PRESSED_STATE){
					subKeyProcess(i);
					longPressedTime[i] = LONG_PRESSED_TIME; //(ms)
				}
			}else{
				if(keyReg3[i] == PRESSED_STATE){
					if (longPressedTime[i] > 0){
						longPressedTime[i]--;
						if(longPressedTime[i] == 0){
							longPressedTime[i] = LONG_PRESSED_TIME;
							button_long_flag[i] = 1;
						}
					}
				}
			}
		}
	}
}
