#include <Arduino.h>
#include <led.h>

#ifndef LED_PIN
#define LED_PIN (12)
#endif

#ifndef LED_R
#define LED_R (15)
#endif

#ifndef LED_G
#define LED_G (14)
#endif

#ifndef LED_B
#define LED_B (13)
#endif

// Create a simple led connected to pin 4
led_t my_led(LED_PIN);
led_rgb_t my_led_rgb(LED_R, LED_G, LED_B, true);

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
