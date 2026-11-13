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
  if (_enabled)
  {
    deactivate();
  }
  else
  {
    activate();
  }
}

void ConfigurableMacroAction::activate()
{
  if (_config == nullptr || _enabled)
  {
    return;
  }

  executeActions(
      _config->onActions,
      _config->onActionCount);

  _enabled = true;
}

void ConfigurableMacroAction::deactivate()
{
  if (_config == nullptr || !_enabled)
  {
    return;
  }

  executeActions(
      _config->offActions,
      _config->offActionCount);

  _enabled = false;
}

bool ConfigurableMacroAction::isActive() const
{
  return _enabled;
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
