#include "FootswitchBank.h"

#include "Footswitch.h"

void FootswitchBank::begin(
    DeviceConfig *config)
{
  _config = config;

  for (uint8_t i = 0; i < MAX_FOOTSWITCHES; i++)
  {
    _footswitches[i] = nullptr;
  }
}

void FootswitchBank::registerFootswitch(
    Footswitch *footswitch,
    uint8_t index)
{
  if (index < MAX_FOOTSWITCHES)
  {
    _footswitches[index] = footswitch;
  }
}

void FootswitchBank::update()
{
  for (uint8_t i = 0; i < MAX_FOOTSWITCHES; i++)
  {
    if (_footswitches[i] != nullptr)
    {
      _footswitches[i]->update();
    }
  }
}

void FootswitchBank::handleScenePress(
    uint8_t index)
{
  Footswitch *pressed = _footswitches[index];

  if (pressed == nullptr)
  {
    return;
  }

  if (pressed->isActive())
  {
    pressed->deactivate();
    return;
  }

  for (uint8_t i = 0; i < MAX_FOOTSWITCHES; i++)
  {
    if (i == index)
    {
      continue;
    }

    Footswitch *other = _footswitches[i];

    if (
        other == nullptr ||
        !_config->footswitches[i].isScene ||
        !other->isActive())
    {
      continue;
    }

    other->deactivate();
  }

  pressed->activate();
}
