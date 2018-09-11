#if defined(TESTFIRMWARE)

#include <Arduino.h>

#include "led.h"

// Create a simple led connected to pin 4
led_t my_led(4);
led_rgb_t my_led_rgb(1, 2, 3, true);

/**
* @brief Arduino function to setup and initialize everything.
*/
extern "C" void setup() {
    my_led.on();
    my_led_rgb.set_color(0xff6600);
}

/**
* @brief Arduino function called in the main loop.
*/
extern "C" void loop() {
    my_led.toggle();
    my_led_rgb.toggle();
    delay(1000);
}

#endif
