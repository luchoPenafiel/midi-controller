#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
public:
  Button(uint8_t pin);

  void begin();
  void update();

  bool wasPressed();
  bool wasReleased();

private:
  uint8_t _pin;

  bool _currentState;
  bool _previousState;

  bool _pressedEvent;
  bool _releasedEvent;

  unsigned long _lastDebounceTime;
  static const unsigned long _debounceDelay = 30;
};

#endif