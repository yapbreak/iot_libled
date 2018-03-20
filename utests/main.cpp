#include <CppUTest/CommandLineTestRunner.h>

#include "ut_led.h"

int main(int argc, const char *argv[])
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
