#include "Led.h"

Led::Led(uint8_t pin)
    : _pin(pin)
{
}

void Led::begin()
{
  pinMode(_pin, OUTPUT);
  off();
}

void Led::on()
{
  digitalWrite(_pin, HIGH);
}

void Led::off()
{
  digitalWrite(_pin, LOW);
}

void Led::set(bool state)
{
  state ? on() : off();
}