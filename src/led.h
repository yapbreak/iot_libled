/*         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                Version 2, December 2004
 *
 * Copyright 2017 Adrien Oliva <olivaa+gitlab@yapbreak.fr>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *        DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 * 0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 */
#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

typedef void (*wiring_set_t)(uint8_t, uint8_t);

class led_t {
    private:
        const uint8_t m_pin;
        const wiring_set_t m_set;
        bool m_on = false;
        uint8_t m_intensity = 0xff;


    public:
        led_t(const uint8_t pin, bool dimable = false);
        ~led_t();

        void on();
        void off();
        void toggle();
        void set_intensity(uint8_t intensity, bool silent = false);
        bool is_on() const;
};

class led_rgb_t {
    private:
        led_t m_red;
        led_t m_green;
        led_t m_blue;

    public:
        led_rgb_t(const uint8_t red_pin, const uint8_t green_pin, const uint8_t blue_pin, bool dimable = false);
        ~led_rgb_t();

        void on();
        void off();
        void toggle();
        void set_color(uint32_t color, bool silent = false);
        bool is_on() const;
};

 #endif
