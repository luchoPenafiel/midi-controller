#ifndef FOOTSWITCH_BANK_H
#define FOOTSWITCH_BANK_H

#include <stdint.h>

#include "DeviceConfig.h"

class Footswitch;

class FootswitchBank
{
public:
  void begin(
      DeviceConfig *config);

  void registerFootswitch(
      Footswitch *footswitch,
      uint8_t index);

  void update();

  void handleScenePress(
      uint8_t index);

private:
  DeviceConfig *_config;

  Footswitch *_footswitches[MAX_FOOTSWITCHES];
};

#endif
