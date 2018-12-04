/*
 * ADSRwave.h
 *
 *  Created on: 13 июл. 2018 г.
 *      Author: Дом
 */

#ifndef INC_ADSRWAVE_H_
#define INC_ADSRWAVE_H_

#include "global.h"

#define MAX_MILLIS 3000

typedef struct {
	float attack;
	float decay;
	float sustain;
	float releaseFrom;
	float release;
	float coeff;
	long prevMillis;
	u8 isADSRon;
	u8 isNoteOffWhileADSR;
	u8 current;
	u16 counter;
} M_ADSRwave_TypeDef;

extern volatile long millis;

void ADSRwave_Init(M_ADSRwave_TypeDef *M);  // module init
void ADSRwave_Update(M_ADSRwave_TypeDef *M, float a, float d, float s, float r,
		float c);
float ADSRwave_Func(M_ADSRwave_TypeDef *M, float param, u8 *isNoteOn);

#endif /* INC_ADSRWAVE_H_ */
