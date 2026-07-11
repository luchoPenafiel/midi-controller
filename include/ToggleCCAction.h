#ifndef TOGGLE_CC_ACTION_H
#define TOGGLE_CC_ACTION_H

#include <Arduino.h>

#include "Action.h"
#include "MidiOut.h"

class ToggleCCAction : public Action
{
public:
  ToggleCCAction(
      MidiOut &midi,
      uint8_t cc,
      uint8_t channel = 1);

  void execute() override;

private:
  MidiOut &_midi;

  uint8_t _cc;
  uint8_t _channel;

  bool _enabled;
};

#endif