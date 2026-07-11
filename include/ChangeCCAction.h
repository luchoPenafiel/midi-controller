#ifndef CHANGE_CC_ACTION_H
#define CHANGE_CC_ACTION_H

#include <Arduino.h>

#include "Action.h"
#include "MidiOut.h"

class ChangeCCAction : public Action
{
public:
  ChangeCCAction(
      MidiOut &midi,
      uint8_t cc,
      uint8_t value = 0,
      uint8_t channel = 1);

  void setValue(uint8_t value);

  void execute() override;

private:
  MidiOut &_midi;

  uint8_t _cc;
  uint8_t _value;
  uint8_t _channel;
};

#endif