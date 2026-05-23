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

        // Daca distanta este mai mica sau egala cu 15 cm, pornim buzzerul
        if (distanta > 0 && distanta <= 15) {
            Buzzer_On();
            LCD_SetCursor(0, 1);
            LCD_SendString("Avertizare!    ");
        } else {
            Buzzer_Off();
            LCD_SetCursor(0, 1);
            LCD_SendString("Liber          ");
        }

        _delay_ms(200); // Pauza scurta inainte de urmatoarea citire
    }
}