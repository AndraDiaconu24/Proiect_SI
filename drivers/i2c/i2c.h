#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <stdint.h>

// Inițializează hardware-ul I2C
void I2C_Init(void);

// Generează condiția de START și trimite adresa dispozitivului
void I2C_Start(uint8_t address);

// Trimite un octet de date
void I2C_Write(uint8_t data);

// Generează condiția de STOP
void I2C_Stop(void);

#endif /* I2C_H */