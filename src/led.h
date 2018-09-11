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

/**
 * @mainpage LibLed
 *
 * This is a small IOT library to easily handle various LEDs.
 */

#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include <Printable.h>

class led_rgb_t;

/**
* @brief Abstract a simple LED, dimable or not.
*
* This is the main LED interface. Given a GPIO pin, you can control through
* this API a simple On/Off LED or a dimable LED with 256 different levels.
*/
class led_t : public Printable {
        /**
        * @brief Allow led_rgb_t access to internal state of LED.
        */
        friend class led_rgb_t;
    protected:
        /**
        * @brief A PIN identifier where LED is connected.
        */
        const uint8_t m_pin;
        /**
        * @brief Internal function use to set GPIO state.
        */
        const bool m_dimable;
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
        virtual ~led_t();

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

        /**
        * @brief Printable interface implementation
        *
        * @param p Print object where human readable LED string will be printed.
        *
        * @return Number of bytes written on `p`.
        */
        virtual size_t printTo(Print &p) const override;
};

/**
 * @brief Abstract a RGB LED, dimable or not.
 *
 * This is a facility to manipulate RGB LED, and aggregate 3 simple LEDs.
 * Given 3 GPIO pin (one for each Red, Green and Blue component), you can
 * control through this API:
 *      \li On/Off of every RGB LED
 *      \li Up to 7 colors with simple RGB LED
 *      \li Up to 16M colors with dimable RGB LED
 */
class led_rgb_t : public Printable {
    private:
        /**
         * @brief Control Red componant of RGB LED.
         */
        led_t m_red;
        /**
         * @brief Control Green componant of RGB LED.
         */
        led_t m_green;
        /**
         * @brief Control Blue componant of RGB LED.
         */
        led_t m_blue;

    public:
        /**
        * @brief Main RGB LED constructor.
        *
        * @param red_pin GPIO connected to the Red component of RGB LED
        *                controlled by this interface.
        * @param green_pin GPIO connected to the Green component of RGB LED
        *                  controlled by this interface.
        * @param blue_pin GPIO connected to the Blue component of RGB LED
        *                 controlled by this interface.
        * @param dimable Flag to define if the given LED is dimable or not.
        *
        * By default, a LED is switched off upon creation, and color is
        * set to bright white (i.e. \#FFFFFF).
        */
        led_rgb_t(const uint8_t red_pin, const uint8_t green_pin, const uint8_t blue_pin, bool dimable = false);
        /**
        * @brief Default destructor.
        */
        virtual ~led_rgb_t();

        /**
        * @brief Switch on controlled LED.
        *
        * Use the color stored in object instance.
        */
        void on();
        /**
        * @brief Switch off controlled LED.
        *
        * Color is stored inside object instance to be resumed at
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
         * @brief Register a now color.
         *
         * @param color New color to set under its hexadecimal representation.
         * @param silent  Flag to tell if new color must be immediately applied.
         *
         * For a dimable RGB LED, all value from 0x000000 to 0xffffff could be
         * valid (depending on hardware capabilities). For a non-dimable RGB
         * LED, as soon as a color componant is non NULL, corresponding
         * component is switched on. This means that color \#01bc00 will be
         * rendered as \#ffff00.
         */
        void set_color(uint32_t color, bool silent = false);
        /**
        * @brief Get logical On/Off LED state.
        *
        * @return On/Off LED state.
        */
        bool is_on() const;

        /**
        * @brief Printable interface implementation
        *
        * @param p Print object where human readable LED string will be printed.
        *
        * @return Number of bytes written on `p`.
        */
        virtual size_t printTo(Print &p) const override;
};

 #endif
