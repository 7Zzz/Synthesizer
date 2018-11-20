/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define MIDI_TX_GPIO_Port GPIOA
#define MIDI_RX_GPIO_Port GPIOA
#define SQ_LEDs_GPIO_Port GPIOA
#define LED_CLK_GPIO_Port GPIOA
#define LED_SET_GPIO_Port GPIOA
#define LED_DATA_GPIO_Port GPIOA

#define LED_A0_GPIO_Port GPIOB
#define LED_A1_GPIO_Port GPIOB
#define MC_CLK_GPIO_Port GPIOB
#define MC_DATA_GPIO_Port GPIOB
#define LED_NEnable_GPIO_Port GPIOB
#define LCD_D7_GPIO_Port GPIOB
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D4_GPIO_Port GPIOB
#define LCD_WS_GPIO_Port GPIOB
#define LCD_E_GPIO_Port GPIOB


#define SQ_LEDs_Pin GPIO_PIN_3
#define LED_CLK_Pin GPIO_PIN_5
#define LED_SET_Pin GPIO_PIN_6
#define LED_DATA_Pin GPIO_PIN_7
#define LED_A0_Pin GPIO_PIN_0
#define LED_A1_Pin GPIO_PIN_1
#define LED_NEnable_Pin GPIO_PIN_12
#define MC_CLK_Pin GPIO_PIN_13
#define MC_DATA_Pin GPIO_PIN_15
#define MIDI_TX_Pin GPIO_PIN_9
#define MIDI_RX_Pin GPIO_PIN_10
#define LCD_D7_Pin GPIO_PIN_4
#define LCD_D6_Pin GPIO_PIN_5
#define LCD_D5_Pin GPIO_PIN_6
#define LCD_D4_Pin GPIO_PIN_7
#define LCD_WS_Pin GPIO_PIN_8
#define LCD_E_Pin GPIO_PIN_9

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
