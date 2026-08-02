#include "ConfigurableMacroAction.h"

ConfigurableMacroAction::ConfigurableMacroAction(
    MidiOut &midi)
    : _midi(midi)
{
  _config = nullptr;
  _enabled = false;
}

void ConfigurableMacroAction::begin(
    FootswitchConfig &config)
{
  _config = &config;
}

void ConfigurableMacroAction::execute()
{
  if (_config == nullptr)
  {
    return;
  }

  if (!_enabled)
  {
    executeActions(
        _config->onActions,
        _config->onActionCount);

    _enabled = true;
  }
  else
  {
    executeActions(
        _config->offActions,
        _config->offActionCount);

    _enabled = false;
  }
}

void ConfigurableMacroAction::executeActions(
    MidiCCAction *actions,
    uint8_t count)
{
  for (uint8_t i = 0; i < count; i++)
  {
    Serial.println("======== ChangeCCAction2 ======== ");
    Serial.println(actions[i].cc);
    Serial.println(actions[i].value);

    _midi.sendControlChange(
        actions[i].cc,
        actions[i].value);
  }
}