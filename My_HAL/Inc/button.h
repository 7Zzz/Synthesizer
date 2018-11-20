///*
// * button.h
// *
// *  Created on: Jul 6, 2018
// *      Author: Roman
// */
//#include "global.h"
//#include "stm32f1xx_hal.h"
//#include "stm32f1xx_hal_gpio.h"
//#include "reg.h"
//
//#ifndef BUTTON_H_
//#define BUTTON_H_
//
//// settings
//#define NUM_OF_BTNs          7
//
//#define BTN1                 0
//#define BTN1_PIN          BTN1_Pin
//#define BTN1_PORT           BTN1_GPIO_Port
//
//#define BTN2                 1
//#define BTN2_PIN          BTN2_Pin
//#define BTN2_PORT          BTN2_GPIO_Port
//
//#define BTN3                 2
//#define BTN3_PIN          BTN3_Pin
//#define BTN3_PORT           BTN3_GPIO_Port
//
//
//
//#define BTN4                 3
//#define BTN4_PIN          BTN5_Pin
//#define BTN4_PORT          BTN5_GPIO_Port
//
//#define BTN5                 4
//#define BTN5_PIN          BTN6_Pin
//#define BTN5_PORT           BTN6_GPIO_Port
//
//#define BTN6                 5
//#define BTN6_PIN          BTN7_Pin
//#define BTN6_PORT          BTN7_GPIO_Port
//
//#define BTN7                 6
//#define BTN7_PIN          BTN8_Pin
//#define BTN7_PORT          BTN8_GPIO_Port
//
//// defines
//#define PRESSED   1
//#define UNPRESSED 0
//#define READ      1
//#define NOREAD    0
//
//#define INTERVAL 50
//
//// types
//typedef struct {
//    GPIO_TypeDef* port;
//    u16 pin;
//    u8 state;
//    volatile u32 prevTime;
//    //u8 readFlag;
//
//}BTN_TypeDef;
//
//
//
//
//// funcs
//void Button_Init(BTN_TypeDef* b, GPIO_TypeDef* port, u16 pin);
//uint8_t BTN_ReadChange(BTN_TypeDef* b);
//
//#endif /* BUTTON_H_ */
