// global defines and variables
#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "stm32f4xx.h"
// System
#define SYSTEM_CORE_CLOCK 168000000
#define MILLIS_IN_HOUR    3600000
#define SYSTIMERTICK      SYSTEM_CORE_CLOCK/16800-1        // 1us ?
#define FREE_CYCLES       ((SYSTEM_CORE_CLOCK)/(SAMPLERATE)) //?  we have this much cycles to calculate our shit

// Audio
#define SAMPLERATE        48000      // Hz
#define AUDIO_BLOCKSIZE   32         // in samples

extern volatile long millis; // global time counter
extern volatile long micros; // global time counter

#endif /* GLOBAL_H_ */
