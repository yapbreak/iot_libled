#ifndef UT_LED_H_FXDBES5N
#define UT_LED_H_FXDBES5N

#include <CppUTest/TestHarness.h>
#include "led.h"
#include "Arduino.h"

TEST_GROUP(basic)
{
};

TEST(basic, nothing)
{
};

TEST_GROUP(simple_led)
{
    void setup()
    {
        fixtures::registerInstance(f);
    }

    void teardown()
    {
        f.check();
    }

    fixtures f;
};

TEST(simple_led, creation)
{
    f.set_expected_call("pinMode", 1);
    f.set_expected_call("digitalWrite", 1);
    f.set_expected_call("analogWrite", 0);
    f.set_expected_pin_mode(1, OUTPUT);
    f.set_expected_analog_value(1, UNDEFINED);
    f.set_expected_digital_value(1, LOW);
    led_t l(1);
}

TEST(simple_led, dimmable_creation)
{
    f.set_expected_call("pinMode", 1);
    f.set_expected_call("digitalWrite", 0);
    f.set_expected_call("analogWrite", 1);
    f.set_expected_pin_mode(1, OUTPUT);
    f.set_expected_analog_value(1, 0);
    f.set_expected_digital_value(1, UNDEFINED);
    led_t l(1, true);
}

TEST(simple_led, other_pin)
{
    f.set_expected_pin_mode(2, OUTPUT);
    f.set_expected_analog_value(2, UNDEFINED);
    f.set_expected_digital_value(2, LOW);
    led_t l(2);
}

TEST(simple_led, dimmable_other_pin)
{
    f.set_expected_pin_mode(6, OUTPUT);
    f.set_expected_analog_value(6, 0);
    f.set_expected_digital_value(6, UNDEFINED);
    led_t l(6, true);
}

TEST(simple_led, default_off)
{
    led_t l(1);
    CHECK_FALSE(l.is_on());
}

TEST(simple_led, turn_on)
{
    led_t l(1);
    f.set_expected_pin_mode(1, OUTPUT);
    f.set_expected_analog_value(1, UNDEFINED);
    f.set_expected_digital_value(1, HIGH);
    f.set_expected_call("analogWrite", 0);
    f.set_expected_call("digitalWrite", 2);
    l.on();
    CHECK(l.is_on());
}

TEST(simple_led, toggle)
{
    led_t l(1);
    f.set_expected_pin_mode(1, OUTPUT);
    f.set_expected_analog_value(1, UNDEFINED);
    f.set_expected_digital_value(1, LOW);
    f.check();

    l.toggle();
    f.set_expected_digital_value(1, HIGH);
    f.check();
    CHECK(l.is_on());

    l.toggle();
    f.set_expected_digital_value(1, LOW);
    CHECK_FALSE(l.is_on());

    f.set_expected_call("analogWrite", 0);
}

TEST(simple_led, dimable_intensity_change)
{
    led_t l(6, true);

    f.set_expected_pin_mode(6, OUTPUT);
    f.set_expected_analog_value(6, 0);
    f.set_expected_digital_value(6, UNDEFINED);
    f.check();

    l.set_intensity(128);
    f.set_expected_analog_value(6, 128);
    f.check();
    CHECK(l.is_on());

    l.set_intensity(64, true);
    f.set_expected_analog_value(6, 128);
    f.check();
    CHECK(l.is_on());

    l.toggle();
    f.set_expected_analog_value(6, 0);
    f.check();
    CHECK_FALSE(l.is_on());

    l.toggle();
    f.set_expected_analog_value(6, 64);
    f.check();
    CHECK(l.is_on());
}

TEST_GROUP(print)
{
    void setup()
    {
        fixtures::registerInstance(f);
    }

    void teardown()
    {
        mem.clear();
    }

    fixtures f;
    memory mem;
};

TEST(print, simpleled_default)
{
    led_t l(2);

    l.printTo(mem);
    STRCMP_EQUAL("Led on pin #2 -> 0x255 OFF\n", mem.getcontent().c_str());
};

TEST(print, simpleled_on)
{
    led_t l(2);

    l.on();
    l.printTo(mem);
    STRCMP_EQUAL("Led on pin #2 -> 0x255 ON\n", mem.getcontent().c_str());
};

TEST(print, simpleled_low)
{
    led_t l(3);

    l.set_intensity(LOW);
    l.printTo(mem);
    STRCMP_EQUAL("Led on pin #3 -> 0x25 ON\n", mem.getcontent().c_str());
};

TEST(print, simpleled_high)
{
    led_t l(4);

    l.set_intensity(HIGH, true);
    l.printTo(mem);
    STRCMP_EQUAL("Led on pin #4 -> 0x90 OFF\n", mem.getcontent().c_str());
};

TEST(print, dimableled)
{
    led_t l(8, true);

    l.printTo(mem);
    l.on();
    l.printTo(mem);
    l.set_intensity(20);
    l.printTo(mem);
    l.set_intensity(128, false);
    l.off();
    l.printTo(mem);
    STRCMP_EQUAL("Led on pin #8 [PWM] -> 0x255 OFF\n"
                 "Led on pin #8 [PWM] -> 0x255 ON\n"
                 "Led on pin #8 [PWM] -> 0x20 ON\n"
                 "Led on pin #8 [PWM] -> 0x128 OFF\n",
                 mem.getcontent().c_str());
};


#endif /* end of include guard: UT_LED_H_FXDBES5N */
