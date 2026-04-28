#include "buzzer.h"


void Buzzer_Init(void) {
    // Setează pinul buzzerului ca ieșire (1 în registrul Data Direction)
    BUZZER_DDR |= (1 << BUZZER_PIN);
    
    // Asigură-te că buzzerul este oprit la inițializare
    Buzzer_Off();
}

void Buzzer_On(void) {
    // Setează pinul pe HIGH (1 în registrul PORT)
    BUZZER_PORT |= (1 << BUZZER_PIN);
}

void Buzzer_Off(void) {
    // Setează pinul pe LOW (0 în registrul PORT)
    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}

void Buzzer_Toggle(void) {
    // Inversează starea pinului folosind XOR
    BUZZER_PORT ^= (1 << BUZZER_PIN);
}