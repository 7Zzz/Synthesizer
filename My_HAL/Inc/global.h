/*
 * global.h
 *
 *  Created on: Jul 10, 2018
 *      Author: Roman
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "stdint.h"
#include "stdio.h"

#define OK    1
#define FAIL 0

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;


extern volatile uint32_t millis; // global ms counter

#endif /* GLOBAL_H_ */
