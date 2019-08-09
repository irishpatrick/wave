#include "Led.h"
#include <Arduino.h>

Led::Led() :
   digital(0),
   pwm(0),
   pin(-1),
   mode(0)
{
}

Led::~Led()
{
}

void Led::init(int p, bool m)
{
    pin = p;
    pinMode(pin, OUTPUT);
    mode = m;
}

void Led::on()
{
    digital = 1;
    update();
}

void Led::off()
{
    digital = 0;
    update();
}

void Led::update()
{
    if (mode)
    {
        analogWrite(pin, pwm);
    }
    else
    {
        digitalWrite(pin, digital);
    }
}

void Led::setBrightness(int b)
{
    pwm = map(b, 0, 100, 0, 1023);
}
