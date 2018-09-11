/**
 * @file simple.cpp
 * @brief Simple blinker with a LED connected to PIN 4.
*/

/// [Blinker]
#include <Arduino.h>

#include "led.h"

// Create a simple led connected to pin 4
led_t my_led(4);

/**
* @brief Arduino function to setup and initialize everything.
*/
// cppcheck-suppress unusedFunction
extern "C" void setup() {
    Serial.begin(115200);
    my_led.on();
}

/**
* @brief Arduino function called in the main loop.
*/
// cppcheck-suppress unusedFunction
extern "C" void loop() {
    my_led.toggle();
    sleep(1000);
}

/// [Blinker]
