#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "utils/delay.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/lcd/lcd.h"
#include "drivers/ultrasonic/ultrasonic.h"


int main(void) {
    Buzzer_Init();


   while(1){
    Buzzer_On();
    Delay(1000);
    Buzzer_Off();
    Delay(1000);
   }
}