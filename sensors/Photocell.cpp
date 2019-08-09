#include "Photocell.h"
#include <Arduino.h>

Photocell::Photocell() :
    m_val(0),
    m_last(0),
    m_min(-1),
    m_max(-1),
    m_pin(-1),
    m_delta(0),
    m_last_delta(0),
    m_th(50)
{
}

Photocell::~Photocell()
{
}

void Photocell::init(int pin)
{
    pinMode(pin, INPUT);
    m_pin = pin;
    m_min = analogRead(m_pin);
    m_max = m_min;
}

void Photocell::calibrate()
{
    int raw = analogRead(m_pin);
    m_min = min(m_min, raw);
    m_max = max(m_max, raw);
}

void Photocell::setThreshold(int val)
{
    m_th = val;
}

void Photocell::poll()
{
    m_last = m_val;
    m_val = read();
    
    m_last_delta = m_delta;
    m_delta = m_val - m_last;
}

int Photocell::triggered()
{
    return get() > m_th;
}

int Photocell::peaked()
{
    return 0;
}

int Photocell::get()
{
    return m_val;
}

int Photocell::read()
{
    return map(analogRead(m_pin), m_min, m_max, 0, 100);
}
