#ifndef TOGGLE_MACRO_ACTION_H
#define TOGGLE_MACRO_ACTION_H

#include <Arduino.h>

#include "Action.h"

class ToggleMacroAction : public Action
{
public:
  ToggleMacroAction();

  void addOnAction(Action *action);
  void addOffAction(Action *action);

  void execute() override;

  void activate() override;

  void deactivate() override;

  bool isActive() const override;

private:
  static constexpr uint8_t MAX_ACTIONS = 8;

  Action *_onActions[MAX_ACTIONS];
  Action *_offActions[MAX_ACTIONS];

  uint8_t _onCount;
  uint8_t _offCount;

  bool _enabled;
};

#endif