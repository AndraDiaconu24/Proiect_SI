#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <avr/io.h>
#include <util/delay.h>

// Definirea pinilor
#define TRIG_PORT PORTD
#define TRIG_DDR  DDRD
#define TRIG_PIN  PD2

// ECHO trebuie să fie pe PB0 (ICP1 - Input Capture Pin 1)
#define ECHO_PORT PORTB
#define ECHO_DDR  DDRB
#define ECHO_PIN  PB0

// Funcții
void Ultrasonic_Init(void);
uint16_t Ultrasonic_GetDistance(void);

#endif /* ULTRASONIC_H */