#pragma once

#include <Arduino.h>

constexpr uint8_t MAX_FOOTSWITCHES = 5;
constexpr uint8_t MAX_ACTIONS_PER_STATE = 10;
constexpr uint8_t MAX_NAME_LENGTH = 32;

struct MidiCCAction
{
  uint8_t cc;
  uint8_t value;
};

struct FootswitchConfig
{
  char name[MAX_NAME_LENGTH];

  MidiCCAction onActions[MAX_ACTIONS_PER_STATE];
  uint8_t onActionCount;

  MidiCCAction offActions[MAX_ACTIONS_PER_STATE];
  uint8_t offActionCount;
};

struct DeviceConfig
{
  uint8_t midiChannel;

  FootswitchConfig footswitches[MAX_FOOTSWITCHES];
};