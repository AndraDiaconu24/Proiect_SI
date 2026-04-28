#include "ultrasonic.h"
#include "drivers/timer/timer1.h"

void Ultrasonic_Init(void) {
    // Setăm TRIG ca Output
    TRIG_DDR |= (1 << TRIG_PIN);
    // Asigurăm că TRIG este LOW inițial
    TRIG_PORT &= ~(1 << TRIG_PIN);
    
    // Setăm ECHO (PB0/ICP1) ca Input
    ECHO_DDR &= ~(1 << ECHO_PIN);
    // Activăm rezistența de pull-up pe ECHO (opțional, dar recomandat)
    ECHO_PORT |= (1 << ECHO_PIN);
    
    // Inițializăm Timer1 pentru Input Capture
    Timer1_InputCapture_Init();
}

uint16_t Ultrasonic_GetDistance(void) {
    uint16_t start_time, end_time, pulse_ticks;
    
    // 1. Generăm pulsul de Trigger de 10us
    TRIG_PORT |= (1 << TRIG_PIN);
    _delay_us(10);
    TRIG_PORT &= ~(1 << TRIG_PIN);
    
    // 2. Curățăm flag-ul de Input Capture (ICF1) scriind logic 1 pe el
    TIFR1 = (1 << ICF1);
    
    // 3. Setăm Input Capture să detecteze Frontul Crescător (Rising Edge)
    TCCR1B |= (1 << ICES1);
    
    // Așteptăm frontul crescător (când ECHO trece în HIGH)
    // Atenție: În producție se pune un timeout aici pentru a nu bloca codul infinit
    while ((TIFR1 & (1 << ICF1)) == 0);
    
    // Salvăm valoarea la care a pornit pulsul
    start_time = ICR1;
    
    // Curățăm flag-ul pentru următoarea detecție
    TIFR1 = (1 << ICF1);
    
    // 4. Setăm Input Capture să detecteze Frontul Descrescător (Falling Edge)
    TCCR1B &= ~(1 << ICES1);
    
    // Așteptăm frontul descrescător (când ECHO trece înapoi în LOW)
    while ((TIFR1 & (1 << ICF1)) == 0);
    
    // Salvăm valoarea la care s-a terminat pulsul
    end_time = ICR1;
    
    // 5. Calculăm durata pulsului în "ticks" de timer
    // Fiind variabile pe 16 biți (uint16_t), diferența va fi corectă chiar dacă timerul face overflow (trece de 65535)
    pulse_ticks = end_time - start_time;
    
    // 6. Calculăm distanța în centimetri
    // La 16MHz cu prescaler /8, 1 tick = 0.5us
    // Distanța (cm) = Timp(us) / 58
    // Timp(us) = pulse_ticks * 0.5 = pulse_ticks / 2
    // Distanța = (pulse_ticks / 2) / 58 = pulse_ticks / 116
    
    return pulse_ticks / 116;
}