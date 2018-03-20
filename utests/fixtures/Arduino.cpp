#include <map>
#include <sstream>
#include <string>
#include "Arduino.h"
#include <CppUTest/TestHarness.h>

fixtures *fixtures::s_fixtures;
fixtures *fixtures::getInstance()
{
    return s_fixtures;
}
void fixtures::registerInstance(fixtures &f)
{
    s_fixtures = &f;
}

void analogWrite(uint8_t pin, uint8_t value)
{
    fixtures *f = fixtures::getInstance();
    BYTES_EQUAL(OUTPUT, f->get_actual_pin_mode(pin));

    f->set_actual_analog_value(pin, value);
    f->call("analogWrite");
}
void digitalWrite(uint8_t pin, uint8_t value)
{
    fixtures *f = fixtures::getInstance();
    BYTES_EQUAL(OUTPUT, f->get_actual_pin_mode(pin));

    f->set_actual_digital_value(pin, value);
    f->call("digitalWrite");
}

void pinMode(uint8_t pin, uint8_t mode)
{
    fixtures *f = fixtures::getInstance();

    f->set_actual_pin_mode(pin, mode);
    f->set_actual_analog_value(pin, UNDEFINED);
    f->set_actual_digital_value(pin, UNDEFINED);
    f->call("pinMode");
}

fixtures::fixtures()
    : m_expected_led_map()
    , m_actual_led_map()
    , m_expected_function_call_map()
    , m_actual_function_call_map()
{
}

fixtures::~fixtures()
{
}

void fixtures::set_expected_call(const char *function, int count)
{
    m_expected_function_call_map[function] = count;
}

int fixtures::get_expected_call(const char *function) const
{
    return m_expected_function_call_map.at(function);
}

void fixtures::set_expected_pin_mode(uint8_t pin, uint8_t mode)
{
    m_expected_led_map[pin].mode = mode;
}

uint8_t fixtures::get_expected_pin_mode(uint8_t pin) const
{
    return m_expected_led_map.at(pin).mode;
}

void fixtures::set_expected_digital_value(uint8_t pin, uint16_t level)
{
    m_expected_led_map[pin].digital_value = level;
}

uint8_t fixtures::get_expected_digital_value(uint8_t pin) const
{
    return m_expected_led_map.at(pin).digital_value;
}

void fixtures::set_expected_analog_value(uint8_t pin, uint16_t value)
{
    m_expected_led_map[pin].analog_value = value;
}

uint8_t fixtures::get_expected_analog_value(uint8_t pin) const
{
    return m_expected_led_map.at(pin).analog_value;
}

void fixtures::set_actual_call(const char *function, int count)
{
    m_actual_function_call_map[function] = count;
}

void fixtures::call(const char *function)
{
    int count;
    try {
        count = m_actual_function_call_map.at(function);
    } catch (std::out_of_range) {
        count = 0;
    }

    m_actual_function_call_map[function] = count + 1;
}

int fixtures::get_actual_call(const char *function) const
{
    return m_actual_function_call_map.at(function);
}

void fixtures::set_actual_pin_mode(uint8_t pin, uint8_t mode)
{
    m_actual_led_map[pin].mode = mode;
}

uint8_t fixtures::get_actual_pin_mode(uint8_t pin) const
{
    return m_actual_led_map.at(pin).mode;
}

void fixtures::set_actual_digital_value(uint8_t pin, uint16_t level)
{
    m_actual_led_map[pin].digital_value = level;
}

uint8_t fixtures::get_actual_digital_value(uint8_t pin) const
{
    return m_actual_led_map.at(pin).digital_value;
}

void fixtures::set_actual_analog_value(uint8_t pin, uint16_t value)
{
    m_actual_led_map[pin].analog_value = value;
}

uint8_t fixtures::get_actual_analog_value(uint8_t pin) const
{
    return m_actual_led_map.at(pin).analog_value;
}

void fixtures::check() const
{
    // Function call check
    for (auto it = m_expected_function_call_map.begin();
            it != m_expected_function_call_map.end(); it++) {
        int expected_count = it->second;
        int actual_count;
        try {
            actual_count = m_actual_function_call_map.at(it->first);
        } catch (std::out_of_range) {
            if (expected_count != 0) {
                std::stringstream ss;
                ss << "No call to " << it->first;
                FAIL(ss.str().c_str());
            }
            actual_count = 0;
        }

        std::stringstream expected;
        expected << it->first << ":" << expected_count;

        std::stringstream actual;
        actual << it->first << ":" << actual_count;
        STRCMP_EQUAL(expected.str().c_str(), actual.str().c_str());
    }

    // Pin state check
    for (auto it = m_expected_led_map.begin();
            it != m_expected_led_map.end(); it++) {
    }
}
