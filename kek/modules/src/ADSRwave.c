/*
 * ADSRwave.c
 *
 *  Created on: 13 июл. 2018 г.
 *      Author: Дом
 */
#include "ADSRwave.h"

void ADSRwave_Init(M_ADSRwave_TypeDef *M) {
	M->attack = 0;
	M->decay = 0;
	M->sustain = 0;
	M->release = 0;
	M->releaseFrom = 0;
	M->prevMillis = 0;
	M->isADSRon = 0;
	M->coeff = -1;
	M->current = 0;
	M->counter = 0;
	M->isNoteOffWhileADSR = 0;
}

void ADSRwave_Update(M_ADSRwave_TypeDef *M, float a, float d, float s, float r,
		float c) {
	M->attack = a;
	M->decay = d;
	M->sustain = s;
	M->release = r;
	M->coeff = c;
}

float ADSRwave_Func(M_ADSRwave_TypeDef *M, float param, u8 *isNoteOn) {
	M->counter = millis - M->prevMillis;
	if (*isNoteOn || M->isADSRon) {
		if (!(*isNoteOn) && !M->isNoteOffWhileADSR) {
			M->prevMillis = millis;
			switch (M->current) {
			case 0:
				if(M->coeff >0)
				M->releaseFrom = (float) (M->counter)
						/ (float) (MAX_MILLIS * M->attack);

				break;
			case 1:
				M->releaseFrom = (float) ((MAX_MILLIS * M->decay
						- (1 - M->sustain) * M->counter))
						/ (float) (MAX_MILLIS * M->decay);
				break;
			case 2:
				M->releaseFrom = M->sustain;
				break;
			}
			M->current = 3;
			M->counter = 0;
			M->isNoteOffWhileADSR = 1;
		} else if (*isNoteOn && M->isNoteOffWhileADSR) {
			M->prevMillis = millis;
			M->current = 0;
			M->counter = 0;
			M->isNoteOffWhileADSR = 0;
		}

		switch (M->current) {
		case 0:
			if (!M->isADSRon) {
				M->isADSRon = 1;
				M->prevMillis = millis;
				M->counter = 0;
			}
			if (M->counter < MAX_MILLIS * M->attack) {
				if (M->coeff > 0)
					param = M->coeff * (4 - param)
							* ((float) M->counter
									/ (float) (MAX_MILLIS * M->attack)) + param;
				else
					param = M->coeff * param
							* ((float) M->counter
									/ (float) (MAX_MILLIS * M->attack)) + param;
			} else {
				M->counter = 0;
				M->prevMillis = millis;
				M->current++;
			}
			break;
		case 1:
			if (M->counter < MAX_MILLIS * M->decay) {
				if (M->coeff > 0)
					param = (float) (M->coeff * (4 - param)
							* (MAX_MILLIS * M->decay
									- (1 - M->sustain) * M->counter))
							/ (float) (MAX_MILLIS * M->decay) + param;
				else
					param = (float) (M->coeff * param
							* (MAX_MILLIS * M->decay
									- (1 - M->sustain) * M->counter))
							/ (float) (MAX_MILLIS * M->decay) + param;
			} else {
				M->counter = 0;
				M->prevMillis = millis;
				M->current++;
			}
			break;
		case 2:
			if (*isNoteOn) {
				if (M->coeff > 0)
					param = M->coeff * (4 - param) * M->sustain + param;
				else
					param = M->coeff * param * M->sustain + param;
			} else {
				M->counter = 0;
				M->prevMillis = millis;
				M->current++;
			}
			break;
		case 3:
			if (M->counter < MAX_MILLIS * M->release) {
				if (M->coeff > 0)
					param = (float) (M->coeff * (4-param) * M->releaseFrom
							* (MAX_MILLIS * M->release - M->counter))
							/ (float) (MAX_MILLIS * M->release) + param;
				else
					param = (float) (M->coeff * param * M->releaseFrom
							* (MAX_MILLIS * M->release - M->counter))
							/ (float) (MAX_MILLIS * M->release) + param;
			} else {
				M->counter = 0;
				M->prevMillis = millis;
				M->current = 0;
				M->isADSRon = 0;
			}
			break;
		}
	}
	return param;
}
