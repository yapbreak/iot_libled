#include <map>

#include <CppUTest/CommandLineTestRunner.h>
#include "ut_led.h"
#include "ut_led_rgb.h"


int main(int argc, const char *argv[])
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
