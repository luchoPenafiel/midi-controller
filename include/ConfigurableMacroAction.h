#ifndef CONFIGURABLE_MACRO_ACTION_H
#define CONFIGURABLE_MACRO_ACTION_H

#include "Action.h"
#include "MidiOut.h"
#include "DeviceConfig.h"

class ConfigurableMacroAction : public Action
{
public:
  ConfigurableMacroAction(
      MidiOut &midi);

  void begin(
      FootswitchConfig &config);

  void execute() override;

  void activate() override;

  void deactivate() override;

  bool isActive() const override;

private:
  MidiOut &_midi;

  FootswitchConfig *_config;

  bool _enabled;

  void executeActions(
      MidiCCAction *actions,
      uint8_t count);
};

#endif