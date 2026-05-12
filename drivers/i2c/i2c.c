#include "i2c.h"
#include <util/twi.h>

void I2C_Init(void) {
    // Setează frecvența SCL la 100kHz pentru F_CPU = 16MHz
    // SCL_freq = F_CPU / (16 + 2 * TWBR * Prescaler)
    // 100000 = 16000000 / (16 + 2 * 72 * 1)
    TWSR = 0x00; // Prescaler = 1
    TWBR = 72;   
    TWCR = (1 << TWEN); // Activează modulul TWI
}

void I2C_Start(uint8_t address) {
    // Trimite START
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))); // Așteaptă finalizarea

    // Trimite Adresa
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))); // Așteaptă finalizarea
}

void I2C_Write(uint8_t data) {
    // Încarcă datele
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT))); // Așteaptă finalizarea
}

void I2C_Stop(void) {
    // Trimite STOP
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    // Nu așteptăm după STOP
}