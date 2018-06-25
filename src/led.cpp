/**
 * @file led.cpp
 * @brief LED interface implementation using Arduino framework.
 */
#include "Arduino.h"

#include "led.h"

led_t::led_t(const uint8_t pin, bool dimable)
    : m_pin(pin)
    , m_set(dimable ? reinterpret_cast<wiring_set_t>(analogWrite)
                    : reinterpret_cast<wiring_set_t>(digitalWrite))
{
    pinMode(m_pin, OUTPUT);
    off();
}

led_t::~led_t()
{
}

void led_t::on()
{
    m_set(m_pin, m_intensity);
    m_on = true;
}

void led_t::off()
{
    m_set(m_pin, 0);
    m_on = false;
}

void led_t::toggle()
{
    m_on ? off() : on();
}

void led_t::set_intensity(uint8_t intensity, bool silent)
{
    m_intensity = intensity;
    if (!silent)
        on();
}

bool led_t::is_on() const
{
    return m_on;
}

led_rgb_t::led_rgb_t(const uint8_t red_pin,
                     const uint8_t green_pin,
                     const uint8_t blue_pin,
                     bool dimable)
    : m_red(red_pin, dimable)
    , m_green(green_pin, dimable)
    , m_blue(blue_pin, dimable)
{
}

led_rgb_t::~led_rgb_t()
{
}

void led_rgb_t::on()
{
    m_red.on();
    m_green.on();
    m_blue.on();
}

void led_rgb_t::off()
{
    m_red.off();
    m_green.off();
    m_blue.off();
}

void led_rgb_t::toggle()
{
    m_red.toggle();
    m_green.toggle();
    m_blue.toggle();
}

void led_rgb_t::set_color(uint32_t color, bool silent)
{
    m_red.set_intensity((color >> 16) & 0xff, silent);
    m_green.set_intensity((color >> 8) & 0xff, silent);
    m_blue.set_intensity((color >> 0) & 0xff, silent);
}

bool led_rgb_t::is_on() const
{
    return m_red.is_on() || m_green.is_on() || m_blue.is_on();
}
