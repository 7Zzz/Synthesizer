/*
 * ADSR.h
 *
 *  Created on: 8 июл. 2018 г.
 *      Author: Дом
 */

#ifndef INC_ADSR_H_
#define INC_ADSR_H_

#include "global.h"

#define MAX_MILLIS 3000

typedef struct {
	float attack;
	float decay;
	float sustain;
	float releaseFrom;
	float release;
	long prevMillis;
	u8 isADSRon;
	u8 isNoteOffWhileADSR;
	u8 current;
	u16 counter;
} M_ADSR_TypeDef;

extern volatile long millis;
extern uint8_t numPlayingNotes;

void ADSR_Init(M_ADSR_TypeDef *M);  // module init
void ADSR_Update(M_ADSR_TypeDef *M, float a, float d, float s, float r);
u16 ADSR_Func(M_ADSR_TypeDef *M, u16 param, u8 *isNoteOn);
#endif /* INC_ADSR_H_ */
