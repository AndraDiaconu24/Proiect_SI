#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "utils/delay.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/lcd/lcd.h"
#include "drivers/ultrasonic/ultrasonic.h"
#include "drivers/i2c/i2c.h"

int main(void) {
    // 1. Inițializarea modulelor
    Buzzer_Init();
    Ultrasonic_Init();
    LCD_Init();

    LCD_SetCursor(0, 0);
    LCD_SendString("Salutare!");
    
    LCD_SetCursor(0, 1);
    LCD_SendString("TEST");

    while(1) {
        // --- STAREA 1: Afișăm primul mesaj ---
        LCD_Clear();
        LCD_SetCursor(0, 0);
        LCD_SendString("Sistem Activat");
        
        LCD_SetCursor(0, 1);
        LCD_SendString("Astept 10 sec...");

        // Așteptăm 10 secunde (10 x 1000 ms)
        for (uint8_t i = 0; i < 10; i++) {
            _delay_ms(1000);
        }

        // --- STAREA 2: Schimbăm textul ---
        LCD_Clear();
        LCD_SetCursor(0, 0);
        LCD_SendString("Update Terminat!");
        
        LCD_SetCursor(0, 1);
        LCD_SendString("Totul e OK.");

        // Mai așteptăm 10 secunde înainte să reluăm bucla
        for (uint8_t i = 0; i < 10; i++) {
            _delay_ms(1000);
        }

    }
}