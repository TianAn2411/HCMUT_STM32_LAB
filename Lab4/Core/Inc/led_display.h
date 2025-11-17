/*
 * display.h
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "global.h"

void updateTrafficLight(int state);
void displayAutoTrafficLight();
void displayBlinkTrafficLight();
void displayTime();
void updateCounter();

#endif /* INC_LED_DISPLAY_H_ */
