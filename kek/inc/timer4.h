#ifndef TIMER4_H_
#define TIMER4_H_

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "global.h"

#define TIMER4_FREQ       10000  // Hz
#define TIMER4_PERIOD       10   // counts
#define TIMER4_PRESCALER	(SYSTEM_CORE_CLOCK / TIMER4_FREQ)  //?

void Timer4_Init(void);

#endif /* TIMER4_H_ */
