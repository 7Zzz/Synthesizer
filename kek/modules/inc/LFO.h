/*
 * LFO.h
 *
 *  Created on: 14 июл. 2018 г.
 *      Author: Дом
 */

#ifndef INC_LFO_H_
#define INC_LFO_H_

#include "global.h"
#include "arm_math.h"

#define MAX 200

typedef struct {
	float freq;
	float amp;
	u16 counter;
	u8 wasNoteOn;
	long prevMillis;
} M_LFO_TypeDef;

extern volatile long millis;

void LFO_Init(M_LFO_TypeDef *M);  // module init
void LFO_Update(M_LFO_TypeDef *M, float f, float a);
u16 LFO_Func(M_LFO_TypeDef *M, u16 param, u8 isNoteOn);
float myAbs(float in);
#endif /* INC_LFO_H_ */
