#include "ChangeCCAction.h"

ChangeCCAction::ChangeCCAction(
    MidiOut &midi,
    uint8_t cc,
    uint8_t value,
    uint8_t channel)
    : _midi(midi),
      _cc(cc),
      _value(value),
      _channel(channel)
{
}

void ChangeCCAction::setValue(uint8_t value)
{
  _value = value;
}

void ChangeCCAction::execute()
{
  _midi.sendControlChange(_cc, _value, _channel);
  Serial.println("======== ChangeCCAction ======== ");
  Serial.println(_cc);
  Serial.println(_value);
}