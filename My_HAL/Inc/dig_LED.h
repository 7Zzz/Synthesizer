#ifndef __DIG_LED
#define __DIG_LED

#include <stdio.h>
#include <string.h>
#include "stm32f1xx_hal.h"

//#define WS2812
#define SK6812MINI

//WS2812
#ifdef WS2812
#define DIG_LED_FREQ										(8000000)               // it is fixed: WS2812 require 800kHz
#define TIMER_CLOCK_FREQ									(32000000)   	        // can be modified - multiples of 0.8MHz are suggested
#define TIMER_PERIOD										(TIMER_CLOCK_FREQ / DIG_LED_FREQ)
#define DIG_LED_NUMBER										(1)					    // how many LEDs the MCU should control?
#define LED_DATA_SIZE										(DIG_LED_NUMBER * 24)
#define RESET_SLOTS_BEGIN									(50)
#define RESET_SLOTS_END										(50)
#define DIG_LED_LAST_SLOT									(1)
#define LED_BUFFER_SIZE										(RESET_SLOTS_BEGIN + LED_DATA_SIZE + DIG_LED_LAST_SLOT + RESET_SLOTS_END)

#define DIG_LED_0											(TIMER_PERIOD / 3)		// WS2812's zero high time is long about one third of the period
#define DIG_LED_1											(TIMER_PERIOD * 2 / 3)	// WS2812's one high time is long about two thirds of the period
#define DIG_LED_RESET                                       (0)
#endif


//SK6812MINI
#ifdef SK6812MINI
#define DIG_LED_FREQ                                        (800000)                 // it is fixed: SK6812_mini require 800kHz
#define TIMER_CLOCK_FREQ                                    (32000000)               // can be modified - multiples of 0.8MHz are suggested
#define TIMER_PERIOD                                        (TIMER_CLOCK_FREQ / DIG_LED_FREQ)
#define DIG_LED_NUMBER                                      (16)                      // how many LEDs the MCU should control?
#define LED_DATA_SIZE                                       (DIG_LED_NUMBER * 24)
#define RESET_SLOTS_BEGIN                                   (50)
#define RESET_SLOTS_END                                     (50)
#define DIG_LED_LAST_SLOT                                   (1)
#define LED_BUFFER_SIZE                                     (RESET_SLOTS_BEGIN + LED_DATA_SIZE + DIG_LED_LAST_SLOT + RESET_SLOTS_END)
#define DIG_LED_0                                           (TIMER_PERIOD / 4)        // SK6812_mini's zero high time is long about one fourth of the period
#define DIG_LED_1                                           (TIMER_PERIOD / 2)        // SK6812_mini's one high time is long about half of the period
#define DIG_LED_RESET                                       (0)
#endif



//void DIG_LED_init(void);
void DIG_LED_update(void);

void setLEDcolor(uint32_t LEDnumber, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
void setWHOLEcolor(uint8_t RED, uint8_t GREEN, uint8_t BLUE);
void fillBufferBlack(void);
void fillBufferWhite(void);
//void TIMx_DMA_IRQHandler(void);


typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;// color tone

hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);

/*
typedef struct RgbColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RgbColor;

typedef struct HsvColor
{
    uint8_t h;
    uint8_t s;
    uint8_t v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv);
HsvColor RgbToHsv(RgbColor rgb);
*/

#endif
