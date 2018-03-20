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
    f.set_expected_digital_value(1, 0);
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
    f.set_expected_digital_value(2, 0);
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
    f.set_expected_analog_value(1, UNDEFINED);
    f.set_expected_digital_value(1, 0xff);
    f.set_expected_call("analogWrite", 0);
    f.set_expected_call("digitalWrite", 2);
    l.on();
    CHECK(l.is_on());
}

TEST(simple_led, toggle)
{
    led_t l(1);
    f.set_expected_analog_value(1, UNDEFINED);
    f.set_expected_digital_value(1, 0);
    f.check();

    l.toggle();
    f.set_expected_digital_value(1, 0xff);
    f.check();
    CHECK(l.is_on());

    l.toggle();
    f.set_expected_digital_value(1, 0);
    CHECK_FALSE(l.is_on());

    f.set_expected_call("analogWrite", 0);
}

TEST(simple_led, dimable_intensity_change)
{
    led_t l(6, true);

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


#endif /* end of include guard: UT_LED_H_FXDBES5N */
