#include "lcd.h"
#include "../i2c/i2c.h"
#include <util/delay.h>

uint8_t _backlightval = LCD_BACKLIGHT;

// Funcție internă pentru a trimite date pe magistrala I2C
static void LCD_I2C_Write(uint8_t data) {
    I2C_Start(LCD_I2C_ADDR);
    I2C_Write(data | _backlightval);
    I2C_Stop();
}

// Funcție internă pentru a pulsa pinul EN (Enable)
static void LCD_PulseEnable(uint8_t data) {
    LCD_I2C_Write(data | LCD_EN); // EN = 1
    _delay_us(1);                 // Impuls scurt
    LCD_I2C_Write(data & ~LCD_EN); // EN = 0
    _delay_us(50);                // Timp de procesare pentru LCD
}

// Trimite 4 biți (un nibble) către LCD
static void LCD_SendNibble(uint8_t nibble) {
    LCD_I2C_Write(nibble);
    LCD_PulseEnable(nibble);
}

// Trimite un octet întreg (în modul 4-biți se trimite prima dată partea High, apoi Low)
static void LCD_Send(uint8_t value, uint8_t mode) {
    uint8_t highnib = value & 0xF0;
    uint8_t lownib  = (value << 4) & 0xF0;
    
    LCD_SendNibble(highnib | mode);
    LCD_SendNibble(lownib | mode);
}

void LCD_Clear(void) {
    LCD_Send(0x01, 0); // Comanda Clear Display
    _delay_ms(2);      // Această comandă durează mai mult
}

void LCD_SetCursor(uint8_t col, uint8_t row) {
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 }; // Adresele memoriei DDRAM pentru liniile 0-3
    if (row > 3) row = 3; // Limitare siguranță
    LCD_Send(0x80 | (col + row_offsets[row]), 0); // Comanda Set DDRAM Address
}

void LCD_SendChar(char data) {
    LCD_Send((uint8_t)data, LCD_RS); // RS = 1 pentru Date
}

void LCD_SendString(const char *str) {
    while (*str) {
        LCD_SendChar(*str++);
    }
}

void LCD_Init(void) {
    I2C_Init();
    _delay_ms(50); // Așteaptă ca LCD-ul să pornească complet

    // Secvența obligatorie de inițializare în modul 4-biți
    LCD_SendNibble(0x30);
    _delay_ms(5);
    LCD_SendNibble(0x30);
    _delay_us(150);
    LCD_SendNibble(0x30);
    LCD_SendNibble(0x20); // Trecere oficială în modul 4 biți

    // Configurare LCD: 2 linii, caractere 5x8 (0x28)
    LCD_Send(0x28, 0); 
    
    // Display ON, Cursor OFF, Blink OFF (0x0C)
    LCD_Send(0x0C, 0); 
    
    // Entry Mode: Auto-incrementare cursor, fără shiftare display (0x06)
    LCD_Send(0x06, 0); 
    
    LCD_Clear();
}