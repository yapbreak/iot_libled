#include <Arduino.h>

#include "led.h"

// Create a simple led connected to pin 4
led_t my_led(4);

void setup() {
    Serial.begin(115200);
    my_led.on();
}

void loop() {
    my_led.toggle();
    sleep(1000);
}
