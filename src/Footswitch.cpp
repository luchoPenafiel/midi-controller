#include "Footswitch.h"

#include "FootswitchBank.h"

Footswitch::Footswitch(
    Button &button,
    Led &led,
    Action &action)
    : _button(button),
      _led(led),
      _action(action),
      _config(nullptr),
      _bank(nullptr),
      _index(0)
{
}

void Footswitch::begin(
    FootswitchConfig *config,
    FootswitchBank *bank,
    uint8_t index)
{
  _config = config;
  _bank = bank;
  _index = index;

  _button.begin();
  _led.begin();
}

void Footswitch::update()
{
  _button.update();

  if (!_button.wasPressed())
  {
    return;
  }

  if (
      _config != nullptr &&
      _config->isScene &&
      _bank != nullptr)
  {
    _bank->handleScenePress(_index);
    return;
  }

  _action.execute();
  _led.set(_action.isActive());
}

void Footswitch::activate()
{
  _action.activate();
  _led.set(true);
}

void Footswitch::deactivate()
{
  _action.deactivate();
  _led.set(false);
}

bool Footswitch::isActive() const
{
  return _action.isActive();
}
