/*
 * lcd.c
 *
 *  Created on: Jul 9, 2018
 *      Author: Roman
 */
#include "lcd.h"

void LCD_Init(void) {

    HAL_Delay(10);
    rs0;
    LCD_WritePinData(3);
    e1;
    delayStupid(); //
    e0;
    HAL_Delay(5);
    LCD_WritePinData(3);
    e1;
    delayStupid(); //
    e0;
    HAL_Delay(1);
    LCD_WritePinData(3);
    e1;
    delayStupid(); //
    e0;
    HAL_Delay(1);
    LCD_SendCommand(0x28); //режим 4 бит, 2 линии (для нашего большого дисплея это 4 линии), шрифт 5х8
    LCD_SendCommand(0x0F); //дисплей включаем (D=1), также включаем пока все курсоры
    LCD_SendCommand(0x01); //уберем мусор
    LCD_SendCommand(0x06); //пишем влево.
    LCD_SendCommand(0x02); //возврат курсора в нулевое положение
    HAL_Delay(1);
    // my
    for(int j = 1; j<20; j++) {
    		LCD_SetPos(j,1);
    	}
    	LCD_Clear();
    	LCD_ReturnHome();
}
void LCD_WritePinData(uint8_t dt) {
    if (((dt >> 3) & 0x01) == 1) {
        d7_set();
    } else {
        d7_reset();
    }
    if (((dt >> 2) & 0x01) == 1) {
        d6_set();
    } else {
        d6_reset();
    }
    if (((dt >> 1) & 0x01) == 1) {
        d5_set();
    } else {
        d5_reset();
    }
    if ((dt & 0x01) == 1) {
        d4_set();
    } else {
        d4_reset();
    }
}

void LCD_SendData(uint8_t dt) {
    rs1;
    LCD_WritePinData(dt >> 4);
    e1;
    delayStupid(); //
    e0;
    delayStupid(); //
    LCD_WritePinData(dt);
    e1;
    delayStupid(); //
    e0;
    delayStupid(); //
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
}

void LCD_SendChar(char ch) {
    LCD_SendData((uint8_t) ch);
    delayStupid(); //
}

void LCD_SendString(char* st) {
    uint8_t i = 0;
    while (st[i] != 0) {
        LCD_SendData(st[i]);
        i++;
    }
}

void LCD_SendCommand(uint8_t dt) {
    rs0;
    LCD_WritePinData(dt >> 4);
    e1;
    delayStupid(); //
    e0;
    delayStupid(); //
    LCD_WritePinData(dt);
    e1;
    delayStupid(); //
    e0;
    HAL_Delay(1);

}

void LCD_SetPos(uint8_t x, uint8_t y) {
    switch (y-1) {
    case 0:
        LCD_SendCommand((x-1) | 0x80);
        break;
    case 1:
        LCD_SendCommand((0x28 + (x-1)) | 0x80);
        break;
    default:
        LCD_SendCommand((x-1) | 0x80);

//    case 2:
//        LCD_SendCommand((0x14 + x) | 0x80);
//        break;
//    case 3:
//        LCD_SendCommand((0x54 + x) | 0x80);
//        break;
    }
}

void LCD_ReturnHome(void) {
    LCD_SendCommand(0x02);
}

void LCD_ShiftCursor(uint8_t dir) {
    LCD_SendCommand(0x04 | (dir << 1));
}

void LCD_ShiftDisplayPage(uint8_t dir) {
    LCD_SendCommand(0x05 | (dir << 1));
}

void LCD_Move(uint8_t what, uint8_t dir) {
	LCD_SendCommand(0x10 | (what << 3) | (dir << 2));
}

void delayStupid(void) {
    volatile uint16_t i;
    for (i = 0; i < 1500; i++) { // 500us
    }
}

void LCD_SetCustomChar(uint8_t char_num, uint8_t * char_data) {
	uint8_t i;
	LCD_SendCommand((1<<6) | (char_num * 8) );
	for (i=0;i<=7;i++) {
		LCD_SendData(char_data[i]);
	}
	_LCD_WRITE_TO_RAM_;
}

// LCD Example:
void LCD_Test(void) {
    char str[100];
    sprintf(str, "Stm32F407VG");
    LCD_SendString(str);
    LCD_SetPos(1, 2);
    sprintf(str, "ARM_mc");
    LCD_SendString(str);
    LCD_SetPos(1, 1);
    LCD_SendChar('a');

    uint8_t user_char[8];
    user_char[0]=0b01110; //А вот тут
    user_char[1]=0b10001; // рисуем
    user_char[2]=0b10001; // наш символ
    user_char[3]=0b10001; //
    user_char[4]=0b10001; // Это типа рыба :-)
    user_char[5]=0b01010;
    user_char[6]=0b10001;
    user_char[7]=0b10001;
    LCD_SetCustomChar(0, user_char); // Наша рыба это символ номер ноль
    LCD_SendData(0); //Выводим символ номер ноль
}
