#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "utils/delay.h"


int main(void) {
    
    PWM_Init(D9,50);

   while(1){

    PWM_SetDutyCycle(D9,12);
    
    Delay(1000);

    
    PWM_SetDutyCycle(D9,25);
    
    Delay(1000);

   }
}