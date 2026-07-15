#include "Footswitch.h"

Footswitch::Footswitch(
    Button &button,
    Led &led,
    Action &action)
    : _button(button),
      _led(led),
      _action(action),
      _enabled(false)
{
}

void Footswitch::begin()
{
  _button.begin();
  _led.begin();
}

void Footswitch::update()
{
  _button.update();

  if (_button.wasPressed())
  {
    _enabled = !_enabled;

    _action.execute();

    _led.set(_enabled);
  }
}