#pragma once

#include <Arduino.h>

#include "DeviceConfigManager.h"

class UsbConfigServer
{
public:
  void begin(
      DeviceConfigManager *config);

  void loop();

private:
  String inputBuffer;

  DeviceConfigManager *configManager;

  void processCommand(
      const String &command);

  void sendConfig();

  void sendFootswitchConfig(
      FootswitchConfig &footswitch);
};