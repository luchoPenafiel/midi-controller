#pragma once

#include <Arduino.h>
#include <Preferences.h>

#include "DeviceConfig.h"

class DeviceConfigManager
{
public:
  void begin();

  DeviceConfig *getConfig();

  void save();

  bool setConfigFromJson(
      const String &json);

private:
  Preferences preferences;

  DeviceConfig config;

  void load();

  void setDefaults();
};