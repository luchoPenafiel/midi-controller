#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include "Button.h"
#include "Led.h"
#include "Action.h"

class Footswitch
{
public:
  Footswitch(
      Button &button,
      Led &led,
      Action &action);

  void begin();

  void update();

private:
  Button &_button;
  Led &_led;
  Action &_action;

  bool _enabled;
};

#endif