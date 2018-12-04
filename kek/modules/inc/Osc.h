#ifndef OSC_H_
#define OSC_H_

#include "global.h"
#include "ADSR.h"
#include <math.h>
#include "arm_math.h"

typedef struct {
	//FuncPointerTypeDef OscFunc;          // pointer to osc function
	float oB_samples[AUDIO_BLOCKSIZE];                 // outbut buffer
	float *oBptr;            // output buffer unload address
	float per[1000];
	u16 amp;
	u16 genCnt;                     // counter for waveForm
	u16 smpInPeriod;                // like frequency
	float wavFrm;                        // wave form (0 -- 3999)
	float fldPow;                        // folder power (0 -- 999)
//	u16 tenPow;                        // tension power (0 -- 999)
//	u16 skwPow;                        // skew power (0 -- 999)
	u8 regenerate;
} M_OscTypeDef;

void Osc_Init(M_OscTypeDef *M);  // module init
void OscFunc(M_OscTypeDef *M, u16 amp, u16 smpInPer, float wavFrm, float fldPow);  // module function
void waveForm(M_OscTypeDef *M);  // module function
void folder(M_OscTypeDef *M);
void skewer(M_OscTypeDef *M);
void tension(M_OscTypeDef *M);
u16 tt(M_OscTypeDef *M, u16 i);
float my_exp(float x);
int myCeil(float in);
int myRound(float in);
u16 myAbsMinus(u16 task1, u16 task2);
#endif /* OSC_H_ */
