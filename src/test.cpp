#if defined(TESTFIRMWARE) || defined(SIMULATE)

#ifndef SIMULATE
#include <Arduino.h>
#else
#include "simulate.h"
#endif

#include "led.h"

// Create a simple led connected to pin 4
led_t my_led(4);

/**
* @brief Arduino function to setup and initialize everything.
*/
void setup() {
    my_led.on();
}

/**
* @brief Arduino function called in the main loop.
*/
void loop() {
    my_led.toggle();
    delay(1000);
}

#endif
