#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include <Arduino.h>
#include "Action.h"

class ActionManager
{
public:
  ActionManager();

  void assignAction(uint8_t buttonIndex, Action *action);

  void execute(uint8_t buttonIndex);

private:
  static constexpr uint8_t MAX_BUTTONS = 6;

  Action *_actions[MAX_BUTTONS];
};

#endif