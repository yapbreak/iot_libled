#ifndef UT_LED_RGB_H_L6MAWOEO
#define UT_LED_RGB_H_L6MAWOEO

#include <CppUTest/TestHarness.h>
#include "led.h"
#include "ArduinoFixtures.h"


TEST_GROUP(simple_rgb)
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

TEST(simple_rgb, creation)
{
    led_rgb_t l(1, 2, 3);
    f.set_expected_call("pinMode", 3);
    f.set_expected_call("digitalWrite", 3);
    f.set_expected_call("analogWrite", 0);
    f.set_expected_pin_mode(1, OUTPUT);
    f.set_expected_pin_mode(2, OUTPUT);
    f.set_expected_pin_mode(3, OUTPUT);
    f.set_expected_analog_value(1, UNDEFINED);
    f.set_expected_analog_value(2, UNDEFINED);
    f.set_expected_analog_value(3, UNDEFINED);
    f.set_expected_digital_value(1, LOW);
    f.set_expected_digital_value(2, LOW);
    f.set_expected_digital_value(3, LOW);
}

TEST(simple_rgb, creation_dimable_other_pin)
{
    led_rgb_t l(5, 6, 7, true);
    f.set_expected_call("pinMode", 3);
    f.set_expected_call("digitalWrite", 0);
    f.set_expected_call("analogWrite", 3);
    f.set_expected_pin_mode(5, OUTPUT);
    f.set_expected_pin_mode(6, OUTPUT);
    f.set_expected_pin_mode(7, OUTPUT);
    f.set_expected_analog_value(5, 0);
    f.set_expected_analog_value(6, 0);
    f.set_expected_analog_value(7, 0);
    f.set_expected_digital_value(5, UNDEFINED);
    f.set_expected_digital_value(6, UNDEFINED);
    f.set_expected_digital_value(7, UNDEFINED);
}

TEST_GROUP(rgb_led)
{
    void setup()
    {
        fixtures::registerInstance(f);
        l = new led_rgb_t(1, 2, 3);
        f.set_expected_pin_mode(1, OUTPUT);
        f.set_expected_pin_mode(2, OUTPUT);
        f.set_expected_pin_mode(3, OUTPUT);
        f.set_expected_analog_value(1, UNDEFINED);
        f.set_expected_analog_value(2, UNDEFINED);
        f.set_expected_analog_value(3, UNDEFINED);
        f.set_expected_digital_value(1, LOW);
        f.set_expected_digital_value(2, LOW);
        f.set_expected_digital_value(3, LOW);
    }

    void teardown()
    {
        f.check();
        delete l;
    }

    fixtures f;
    led_rgb_t *l;
};

TEST(rgb_led, default_off)
{
    CHECK_FALSE(l->is_on());
}

TEST(rgb_led, switch_on)
{
    l->on();
    CHECK(l->is_on());

    f.set_expected_digital_value(1, HIGH);
    f.set_expected_digital_value(2, HIGH);
    f.set_expected_digital_value(3, HIGH);
}

TEST(rgb_led, switch_on_and_off)
{
    l->on();
    CHECK(l->is_on());

    l->off();
    CHECK_FALSE(l->is_on());

    f.set_expected_digital_value(1, LOW);
    f.set_expected_digital_value(2, LOW);
    f.set_expected_digital_value(3, LOW);
}

TEST(rgb_led, toggle)
{
    l->toggle();
    CHECK(l->is_on());

    f.set_expected_digital_value(1, HIGH);
    f.set_expected_digital_value(2, HIGH);
    f.set_expected_digital_value(3, HIGH);

    f.check();

    l->toggle();
    CHECK_FALSE(l->is_on());

    f.set_expected_digital_value(1, LOW);
    f.set_expected_digital_value(2, LOW);
    f.set_expected_digital_value(3, LOW);
    f.check();

    l->toggle();
    CHECK(l->is_on());

    f.set_expected_digital_value(1, HIGH);
    f.set_expected_digital_value(2, HIGH);
    f.set_expected_digital_value(3, HIGH);
}

TEST_GROUP(dimable_rgb_led)
{
    void setup()
    {
        fixtures::registerInstance(f);
        l = new led_rgb_t(1, 2, 3, true);
        f.set_expected_pin_mode(1, OUTPUT);
        f.set_expected_pin_mode(2, OUTPUT);
        f.set_expected_pin_mode(3, OUTPUT);
        f.set_expected_analog_value(1, 0);
        f.set_expected_analog_value(2, 0);
        f.set_expected_analog_value(3, 0);
        f.set_expected_digital_value(1, UNDEFINED);
        f.set_expected_digital_value(2, UNDEFINED);
        f.set_expected_digital_value(3, UNDEFINED);
    }

    void teardown()
    {
        f.check();
        delete l;
    }

    fixtures f;
    led_rgb_t *l;
};

TEST(dimable_rgb_led, set_new_color)
{
    l->set_color(0x123456);
    f.set_expected_analog_value(1, 0x12);
    f.set_expected_analog_value(2, 0x34);
    f.set_expected_analog_value(3, 0x56);

    CHECK(l->is_on());
    f.check();

    l->set_color(0x42dead);
    f.set_expected_analog_value(1, 0x42);
    f.set_expected_analog_value(2, 0xde);
    f.set_expected_analog_value(3, 0xad);

    CHECK(l->is_on());
}

TEST(dimable_rgb_led, set_new_color_silent)
{
    l->set_color(0x123456, true);
    CHECK_FALSE(l->is_on());
    f.check();
    l->on();
    f.set_expected_analog_value(1, 0x12);
    f.set_expected_analog_value(2, 0x34);
    f.set_expected_analog_value(3, 0x56);
    CHECK(l->is_on());
}

TEST(dimable_rgb_led, pure_color_checks)
{
    l->set_color(0x000000);
    CHECK(l->is_on());
    f.check();

    l->set_color(0xff0000);
    CHECK(l->is_on());
    f.set_expected_analog_value(1, 0xff);
    f.check();

    l->set_color(0x00ff00);
    CHECK(l->is_on());
    f.set_expected_analog_value(1, 0x00);
    f.set_expected_analog_value(2, 0xff);
    f.check();

    l->set_color(0x0000ff);
    CHECK(l->is_on());
    f.set_expected_analog_value(2, 0x00);
    f.set_expected_analog_value(3, 0xff);
    f.check();

    l->off();
    f.set_expected_analog_value(1, 0);
    f.set_expected_analog_value(2, 0);
    f.set_expected_analog_value(3, 0);
}

TEST(print, simpleledrgb)
{
    led_rgb_t l(1, 2, 3);
    l.printTo(mem);
    STRCMP_EQUAL("Led RGB {#1, #2, #3} -> #255255255 OFF\n",
                 mem.getcontent().c_str());
}

TEST(print, simpleledrgb_othercolor)
{
    led_rgb_t l(4, 5, 6);
    l.set_color(0x12ab30);
    l.printTo(mem);
    STRCMP_EQUAL("Led RGB {#4, #5, #6} -> #1817148 ON \n",
                 mem.getcontent().c_str());
}

TEST(print, simpleledrgb_dimable)
{
    led_rgb_t l(1, 2, 3, true);
    l.printTo(mem);
    STRCMP_EQUAL("Led RGB {#1, #2, #3} -> #255255255 OFF [PWM]\n",
                 mem.getcontent().c_str());
}

TEST(print, simpleledrgb_othercolor_dimable)
{
    led_rgb_t l(4, 5, 6, true);
    l.set_color(0x12ab30);
    l.printTo(mem);
    STRCMP_EQUAL("Led RGB {#4, #5, #6} -> #1817148 ON  [PWM]\n",
                 mem.getcontent().c_str());
}


#endif /* end of include guard: UT_LED_RGB_H_L6MAWOEO */
