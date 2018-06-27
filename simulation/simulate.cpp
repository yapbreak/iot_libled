#ifdef SIMULATE

#include "led.h"
#include "simulate.h"
#include <time.h>
#include <stdio.h>

extern void setup();
extern void loop();

int main(int argc, const char *argv[])
{
    (void) argc;
    (void) argv;

    setup();

    for (;;)
        loop();

    return 0;
}

void pinMode(uint8_t pin, uint8_t mode)
{
    printf("Set pin#%d to %c\n", pin, mode);
}

void analogWrite(uint8_t pin, uint8_t value)
{
    printf("Write on pin#%d to 0x%x\n", pin, value);
}

void digitalWrite(uint8_t pin, uint8_t value)
{
    switch (value) {
        case LOW:
            printf("Write on pin#%d to LOW\n", pin);
            break;
        case HIGH:
            printf("Write on pin#%d to HIGH\n", pin);
            break;
        default:
            printf("Write on pin#%d unexpected value 0x%x\n", pin, value);
            break;
    }
}

void delay(unsigned long ms)
{
    struct timespec waiting;

    time_t seconds = ms / 1000;
    long nanoseconds = (ms % 1000) * 1000;
    waiting.tv_sec = seconds;
    waiting.tv_nsec = nanoseconds;
    nanosleep(&waiting, &waiting);
}

#endif
