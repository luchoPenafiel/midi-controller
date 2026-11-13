#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include "Button.h"
#include "Led.h"
#include "Action.h"
#include "DeviceConfig.h"

class FootswitchBank;

class Footswitch
{
public:
  Footswitch(
      Button &button,
      Led &led,
      Action &action);

  void begin(
      FootswitchConfig *config,
      FootswitchBank *bank,
      uint8_t index);

  void update();

  void activate();

  void deactivate();

  bool isActive() const;

private:
  Button &_button;
  Led &_led;
  Action &_action;

  FootswitchConfig *_config;
  FootswitchBank *_bank;
  uint8_t _index;
};

#endif
