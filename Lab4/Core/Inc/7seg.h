/*
 * 7seg.h
 *
 *  Created on: Nov 5, 2025
 *      Author: Admin
 */

#ifndef INC_7SEG_H_
#define INC_7SEG_H_

#include "global.h"

void display7SEG(int road_way, int num);
void update7SEG(int index);
void updateLEDBuffer(int road_way, int num);
void clearLED();
void clear7SEG();
//note that there is 4 7SEG: index 0 and 1 is for way 1, 2 and 3 for way 2
#endif /* INC_7SEG_H_ */
