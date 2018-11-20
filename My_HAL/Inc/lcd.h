/*
 * lcd.h
 *
 *  Created on: Jul 9, 2018
 *      Author: Roman
 */
#include "stm32f1xx_hal.h"

#ifndef LCD_H_
#define LCD_H_

// settings
#define LCD_PORT   GPIOA
#define LCD_D4     GPIO_PIN_11
#define LCD_D5     GPIO_PIN_10
#define LCD_D6     GPIO_PIN_9
#define LCD_D7     GPIO_PIN_8
#define LCD_RS     GPIO_PIN_15
#define LCD_E      GPIO_PIN_12

//defines
#define LCD_RIGHT   1
#define LCD_LEFT    0
#define LCD_CURSOR  0
#define LCD_DISPLAY 1

// macro
#define d4_set()   HAL_GPIO_WritePin(LCD_PORT, LCD_D4, GPIO_PIN_SET)
#define d5_set()   HAL_GPIO_WritePin(LCD_PORT, LCD_D5, GPIO_PIN_SET)
#define d6_set()   HAL_GPIO_WritePin(LCD_PORT, LCD_D6, GPIO_PIN_SET)
#define d7_set()   HAL_GPIO_WritePin(LCD_PORT, LCD_D7, GPIO_PIN_SET)
#define d4_reset() HAL_GPIO_WritePin(LCD_PORT, LCD_D4, GPIO_PIN_RESET)
#define d5_reset() HAL_GPIO_WritePin(LCD_PORT, LCD_D5, GPIO_PIN_RESET)
#define d6_reset() HAL_GPIO_WritePin(LCD_PORT, LCD_D6, GPIO_PIN_RESET)
#define d7_reset() HAL_GPIO_WritePin(LCD_PORT, LCD_D7, GPIO_PIN_RESET)

#define e1         HAL_GPIO_WritePin(LCD_PORT, LCD_E,  GPIO_PIN_SET)    // установка линии E в 1
#define e0         HAL_GPIO_WritePin(LCD_PORT, LCD_E,  GPIO_PIN_RESET)  // установка линии E в 0
#define rs1        HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_SET)    // установка линии RS в 1 (данные)
#define rs0        HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_RESET)  // установка линии RS в 0 (команда)

#define _LCD_WRITE_TO_RAM_    LCD_SendCommand(1<<7)
#define CURSOR_ON       1
#define CURSOR_OFF      0
#define CURSOR_BLINK    1
#define CURSOR_NOBLINK  0
#define DISPLAY_ON      1
#define DISPLAY_OFF     0
#define _LCD_STATE(__CURS__, __BLNK__, __DISP__)  (LCD_SendCommand( (1<<3) | (__BLNK__<<0) | (__CURS__<<1) | (__DISP__<<2) ))


void LCD_Init(void);                     //
void LCD_SendChar(char ch);              //
void LCD_SendString(char* st);           //=> LCD interface
void LCD_SetPos(uint8_t x, uint8_t y);   //
void LCD_Clear(void);                    //
void LCD_ReturnHome(void);
void LCD_ShiftCursor(uint8_t dir);
void LCD_ShiftDisplayPage(uint8_t dir);
void LCD_Move(uint8_t what, uint8_t dir);
void LCD_SetCustomChar(uint8_t char_num, uint8_t * char_data);


void LCD_Test(void);                       // LCD test

void LCD_WritePinData(uint8_t dt);       //
void delayStupid(void);                  //=> hidden functions
void LCD_SendCommand(uint8_t dt);        //
void LCD_SendData(uint8_t dt);           //


#endif /* LCD_H_ */
