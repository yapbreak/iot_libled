#ifndef ARDUINO_H_NID3LW9T
#define ARDUINO_H_NID3LW9T

#include <stdint.h>

/* Arduino fixtures */

/********************
*  Arduino wiring  *
********************/
void analogWrite(uint8_t pin, uint8_t value);
void digitalWrite(uint8_t pin, uint8_t value);

#define OUTPUT (1)
void pinMode(uint8_t pin, uint8_t mode);

#endif /* end of include guard: ARDUINO_H_NID3LW9T */
