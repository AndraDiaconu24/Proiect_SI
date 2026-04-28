#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "utils/delay.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/lcd/lcd.h"
#include "drivers/ultrasonic/ultrasonic.h"

int main(void) {
    // 1. Inițializarea modulelor
    Buzzer_Init();
    Ultrasonic_Init();

    // Variabilă pentru stocarea distanței măsurate
    uint16_t distanta = 0;

    while(1) {
        // 2. Citim distanța în centimetri de la senzor
        distanta = Ultrasonic_GetDistance();

        // 3. Logica de control a buzzer-ului
        // Verificăm dacă distanța este sub 30 cm și validă (mai mare ca 0)
        if (distanta > 0 && distanta < 30) {
            Buzzer_On();
        } else {
            Buzzer_Off();
        }

        // 4. Pauză între citiri
        // Este obligatoriu un mic delay! Senzorul HC-SR04 are nevoie de 
        // minimum 60ms între măsurători pentru a se asigura că "ecoul" 
        // de la citirea anterioară s-a disipat complet și nu interferează.
        Delay(100); 
    }
}