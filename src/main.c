#include <stdio.h>
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
        // Citim distanta
        uint16_t distanta = Ultrasonic_GetDistance();
        
        // Afisam pe LCD
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "Dist: %u cm   ", distanta);
        
        LCD_SetCursor(0, 0);
        LCD_SendString(buffer);

        // Verificam in ce interval se afla distanta pentru a regla buzzerul
        if (distanta > 0 && distanta <= 5) {
            // De la 5 cm in jos: sunet continuu
            LCD_SetCursor(0, 1);
            LCD_SendString("STOP!!!!");
            Buzzer_On();
            _delay_ms(200); // 200ms pauza inainte de urmatoarea citire
        } 
        else if (distanta > 5 && distanta <= 10) {
            // Intre 5 cm si 10 cm: bip rapid
            LCD_SetCursor(0, 1);
            LCD_SendString("PERICOL!!!");
            Buzzer_On();
            _delay_ms(100);
            Buzzer_Off();
            _delay_ms(100); // Total 200ms
        } 
        else if (distanta > 10 && distanta <= 15) {
            // Intre 10 cm si 15 cm: bip rar
            LCD_SetCursor(0, 1);
            LCD_SendString("ATENTIE!");
            Buzzer_On();
            _delay_ms(50);
            Buzzer_Off();
            _delay_ms(350); // Bip scurt, pauza mai lunga (total 400ms)
        } 
        else {
            // Peste 15 cm: buzzer oprit
            LCD_SetCursor(0, 1);
            LCD_SendString("Liber");
            Buzzer_Off();
            _delay_ms(200);
        }
    }
}