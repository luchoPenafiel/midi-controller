#include "ToggleCCAction.h"

ToggleCCAction::ToggleCCAction(
    MidiOut &midi,
    uint8_t cc,
    uint8_t channel)
    : _midi(midi),
      _cc(cc),
      _channel(channel),
      _enabled(false)
{
}

void ToggleCCAction::execute()
{
  _enabled = !_enabled;

  Serial.println("======== ToggleCCAction ======== ");
  Serial.println(_cc);
  Serial.println(_enabled ? 127 : 0);

  _midi.sendControlChange(
      _cc,
      _enabled ? 127 : 0,
      _channel);
}