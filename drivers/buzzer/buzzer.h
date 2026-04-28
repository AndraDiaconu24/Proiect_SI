#ifndef BUZZER_H
#define BUZZER_H

#include <avr/io.h>
#include <stdint.h>

/* --- Configurare Hardware --- */
// Schimbă aceste macro-uri dacă conectezi buzzerul la alt pin.
// D9 pe Arduino Nano corespunde cu Portul B, Pinul 1 (PB1)
#define BUZZER_DDR  DDRB
#define BUZZER_PORT PORTB
#define BUZZER_PIN  PB1

/* --- Prototipuri Funcții --- */

// Inițializează pinul buzzerului ca ieșire
void Buzzer_Init(void);

// Pornește buzzerul
void Buzzer_On(void);

// Oprește buzzerul
void Buzzer_Off(void);

// Schimbă starea buzzerului (dacă e pornit se oprește, și invers)
void Buzzer_Toggle(void);

#endif /* BUZZER_H */