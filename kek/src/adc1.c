/*
 * adc1.c
 *
 *  Created on: Jun 15, 2018
 *      Author: Roman
 */
#include "adc1.h"


ADC_InitTypeDef adc;

void adcInit(void) {
//������������, ������������ � ��� ��� ������������
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//�������������� ������, �� ���� �������� �����

//ADC_StructInit(&adc);
//adc.ADC_Mode = ADC_Mode_AlterTrig ;
//adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
//ADC_Init(ADC1, &adc);
//
////����� � �� ��������(�������� �������)
//adc.ADC_Mode = ADC_Mode_AlterTrig ;
//adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO; #define ADC_ExternalTrigConv_T1_CC1
//ADC_Init(ADC1, &adc);
////PA0 � ���� ���
//GPIO_StructInit(&port);
//port.GPIO_Mode = GPIO_Mode_AF_PP;
//port.GPIO_Pin = GPIO_Pin_0;
//port.GPIO_Speed = GPIO_Speed_2MHz;
//GPIO_Init(GPIOA, &port);

}
