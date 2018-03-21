/**
 * @file led.h
 * @author Adrien Oliva <olivaa+gitlab@yapbreak.fr>
 * @date 2018-03-21
 * @brief Main classes definitions.
 *
 * @section main API description and purpose
 *
 * @subsection ex_blinker Simple Blinker Sample
 * @snippet simple.cpp Blinker
 */
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

/**
* @brief Internal function pointer used to set led level.
*
* Use to store eigther `analog_write` or `digital_write` from Arduino framework.
*/
typedef void (*wiring_set_t)(uint8_t, uint8_t);

/**
* @brief Abstract a simple Led, dimable or not.
*
* This is the main LED interface. Given a GPIO pin, you can control through
* this API a simple On/Off LED or a dimable LED with 256 different levels.
*/
class led_t {
    private:
        /**
        * @brief A PIN identifier where LED is connected.
        */
        const uint8_t m_pin;
        /**
        * @brief Internal function use to set GPIO state.
        */
        const wiring_set_t m_set;
        /**
        * @brief Flag indicate wether LED is terned on or off.
        */
        bool m_on = false;
        /**
        * @brief Intensity to set when LED is switched on.
        */
        uint8_t m_intensity = 0xff;


    public:
        /**
        * @brief Main LED constructor.
        *
        * @param pin GPIO connected to the LED controlled by this interface.
        * @param dimable Flag to define if the given LED is dimable or not.
        *
        * By default, a LED is switched off upon creation, and intensity is
        * set to the higher level (i.e. 255).
        */
        led_t(const uint8_t pin, bool dimable = false);
        /**
        * @brief Default destructor.
        */
        ~led_t();

        /**
        * @brief Switch on controlled LED.
        *
        * Use the intensity stored in object instance.
        */
        void on();
        /**
        * @brief Switch off controlled LED.
        *
        * Intensity level is stored inside object instance to be resumed at
        * same level when LED needs to be switched on again.
        */
        void off();
        /**
        * @brief Toggle LED status.
        *
        * A simple way to switch on or off controlled LED. Just call `on` or
        * `off` method depending on current LED's state.
        */
        void toggle();
        /**
        * @brief Register a new intensity level.
        *
        * @param intensity New intensity level to set.
        * @param silent Flag to tell if new intensity must be immediately
        *        applied.
        *
        * For a dimable LED, all value in the range 0-255 could be valid
        * (depending on hardware capabilities). For a non-dimable LED, a 0
        * intensity means logical LOW level (i.e. LED switched off) and any
        * other positive value means logical HIGH level (i.e. LED switch on).
        *
        * @note The LED intensity is not correlated to the logical On/Off state
        * which means that you can have a On LED with 0 intensity that results
        * in no light.
        */
        void set_intensity(uint8_t intensity, bool silent = false);
        /**
        * @brief Get logical On/Off LED state.
        *
        * @return On/Off LED state.
        */
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
