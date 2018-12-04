/*
 * ADSR.c
 *
 *  Created on: 8 июл. 2018 г.
 *      Author: Дом
 */

#include "ADSR.h"

void ADSR_Init(M_ADSR_TypeDef *M) {
	M->attack = 0.3;
	M->decay = 0.2;
	M->sustain = 0.7;
	M->release = 0.2;
	M->releaseFrom = 0;
	M->prevMillis = 0;
	M->isADSRon = 0;
	M->current = 0;
	M->counter = 0;
	M->isNoteOffWhileADSR = 0;
}

void ADSR_Update(M_ADSR_TypeDef *M, float a, float d, float s, float r) {
	M->attack = a;
	M->decay = d;
	M->sustain = s;
	M->release = r;
}

u16 ADSR_Func(M_ADSR_TypeDef *M, u16 param, u8 *isNoteOn) {
	M->counter = millis - M->prevMillis;
	if (*isNoteOn || M->isADSRon) {
		if (!(*isNoteOn) && M->current != 3) {
			M->prevMillis = millis;
			switch (M->current) {
			case 0:
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
		} else if (*isNoteOn && M->current == 3) {
			M->current = 0;
			M->isADSRon = 0;
		}

		switch (M->current) {
		case 0:
			if (!M->isADSRon) {
				M->isADSRon = 1;
				M->prevMillis = millis;
				M->counter = 0;
			}
			if (M->counter < MAX_MILLIS * M->attack) {
				param = (float) (param * M->counter)
						/ (float) (MAX_MILLIS * M->attack);
			} else {
				M->counter = 0;
				M->prevMillis = millis;
				M->current++;
			}
			break;
		case 1:
			if (M->counter < MAX_MILLIS * M->decay) {
				param =
						(float) (param
								* (MAX_MILLIS * M->decay
										- (1 - M->sustain) * M->counter))
								/ (float) (MAX_MILLIS * M->decay);
			} else {
				M->counter = 0;
				M->prevMillis = millis;
				M->current++;
			}
			break;
		case 2:
			param = (float) (param * M->sustain);
			break;
		case 3:
			if (M->counter < MAX_MILLIS * M->release) {
				param = (float) (param * M->releaseFrom
						* (MAX_MILLIS * M->release - M->counter))
						/ (float) (MAX_MILLIS * M->release);
			} else {
				M->counter = 0;
				M->prevMillis = millis;
				M->current = 0;
				M->isADSRon = 0;
				numPlayingNotes--;
			}
			break;
		}
	}
	return param;
}
