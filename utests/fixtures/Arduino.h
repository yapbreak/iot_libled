#ifndef ARDUINO_H_NID3LW9T
#define ARDUINO_H_NID3LW9T

#include <map>
#include <CppUTest/TestHarness.h>
#include <iostream>
#include <string>
#include <stdint.h>

/* Arduino fixtures */

/********************
*  Arduino wiring  *
********************/
void analogWrite(uint8_t pin, uint8_t value);
void digitalWrite(uint8_t pin, uint8_t value);

#define OUTPUT ('O')
#define INPUT  ('I')
#define NOTSET ('X')
#define UNDEFINED (0xffff)
void pinMode(uint8_t pin, uint8_t mode);



/*******************
*  Test fixtures  *
*******************/

struct led_attribute_t
{
    uint8_t mode;
    uint16_t digital_value;
    uint16_t analog_value;

    led_attribute_t()
        : mode(NOTSET)
        , digital_value(UNDEFINED)
        , analog_value(UNDEFINED)
    {}
};

class fixtures
{
    private:
        std::map<uint8_t, led_attribute_t> m_expected_led_map;
        std::map<uint8_t, led_attribute_t> m_actual_led_map;
        std::map<std::string, int> m_expected_function_call_map;
        std::map<std::string, int> m_actual_function_call_map;

        static fixtures *s_fixtures;

    public:
        static fixtures *getInstance();
        static void registerInstance(fixtures &f);
        fixtures();
        ~fixtures();

        void set_expected_call(const char *function, int count);
        int get_expected_call(const char *function) const;

        void set_expected_pin_mode(uint8_t pin, uint8_t mode);
        uint8_t get_expected_pin_mode(uint8_t pin) const;

        void set_expected_digital_value(uint8_t pin, uint16_t level);
        uint8_t get_expected_digital_value(uint8_t pin) const;

        void set_expected_analog_value(uint8_t pin, uint16_t value);
        uint8_t get_expected_analog_value(uint8_t pin) const;

        void set_actual_call(const char *function, int count);
        int get_actual_call(const char *function) const;
        void call(const char *function);

        void set_actual_pin_mode(uint8_t pin, uint8_t mode);
        uint8_t get_actual_pin_mode(uint8_t pin) const;

        void set_actual_digital_value(uint8_t pin, uint16_t level);
        uint8_t get_actual_digital_value(uint8_t pin) const;

        void set_actual_analog_value(uint8_t pin, uint16_t value);
        uint8_t get_actual_analog_value(uint8_t pin) const;

        void check() const;
};

#endif /* end of include guard: ARDUINO_H_NID3LW9T */
