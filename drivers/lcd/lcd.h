#ifndef LCD_H
#define LCD_H

#include <stdint.h>

// Adresa I2C standard pentru PCF8574T este 0x27. 
// ATmega folosește adresa shiftată la stânga cu 1 bit pentru scriere (0x27 << 1 = 0x4E).
#define LCD_I2C_ADDR 0x4E 

// Flag-uri pentru pinii de control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00
#define LCD_EN 0x04 // Enable
#define LCD_RW 0x02 // Read/Write
#define LCD_RS 0x01 // Register Select

// Prototipuri
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_SendString(const char *str);
void LCD_SendChar(char data);

#endif /* LCD_H */