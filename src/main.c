#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "utils/delay.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/lcd/lcd.h"
#include "drivers/ultrasonic/ultrasonic.h"


int main(void) {
    
    PWM_Init(D9,50);

   while(1){

    PWM_SetDutyCycle(D9,12);
    
    Delay(1000);

    
    PWM_SetDutyCycle(D9,24);
    
    Delay(1000);

   }
}