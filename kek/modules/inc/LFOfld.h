/*
 * LFOfld.h
 *
 *  Created on: 14 июл. 2018 г.
 *      Author: Дом
 */

#ifndef INC_LFOFLD_H_
#define INC_LFOFLD_H_

#include "global.h"
#include "arm_math.h"

#define MAXs 200

typedef struct {
	float freq;
	float amp;
	u16 counter;
	u8 wasNoteOn;
	long prevMillis;
} M_LFOfld_TypeDef;

extern volatile long millis;

void LFOfld_Init(M_LFOfld_TypeDef *M);  // module init
void LFOfld_Update(M_LFOfld_TypeDef *M, float f, float a);
float LFOfld_Func(M_LFOfld_TypeDef *M, float param, u8 isNoteOn);
float myAbss(float in);
#endif /* INC_LFOFLD_H_ */
