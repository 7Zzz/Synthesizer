#ifndef MAIN_H_
#define MAIN_H_

//Includes
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_tim.h"
#include "global.h"
#include "button.h"
#include "timer4.h"
#include "codec.h"
#include "encoder.h"
#include "spi.h"
#include "leds.h"
#include "Osc.h"
#include "DAC.h"
#include "ADSR.h"
#include "LFO.h"
#include "LFOfld.h"
#include "ADSRwave.h"
#include "wire.h"

#define MAX_NOTES 4
#define MAX_GENERATORS 4

// my funcs:
void SysTick_Init(void);
uint16_t NoteToSmp(uint8_t note);
float NoteNum_ToFreq(u8 noteNumber) ;
// my vars:
volatile uint8_t updateFlag = 1;
volatile uint8_t toggleDacLR = 0;

#endif /* MAIN_H_ */
