#include "Button.h"

Button::Button(uint8_t pin)
{
  _pin = pin;
  _currentState = HIGH;
  _previousState = HIGH;
  _pressedEvent = false;
  _releasedEvent = false;
  _lastDebounceTime = 0;
}

void Button::begin()
{
  pinMode(_pin, INPUT_PULLUP);

  _currentState = digitalRead(_pin);
  _previousState = _currentState;
}

void Button::update()
{
  _pressedEvent = false;
  _releasedEvent = false;

  bool reading = digitalRead(_pin);

  if (reading != _previousState)
  {
    _lastDebounceTime = millis();
  }

  if ((millis() - _lastDebounceTime) > _debounceDelay)
  {
    if (reading != _currentState)
    {
      _currentState = reading;

      if (_currentState == LOW)
      {
        _pressedEvent = true;
      }
      else
      {
        _releasedEvent = true;
      }
    }
  }

  _previousState = reading;
}

bool Button::wasPressed()
{
  return _pressedEvent;
}

bool Button::wasReleased()
{
  return _releasedEvent;
}