#ifndef MIDI_OUT_H
#define MIDI_OUT_H

#include <Arduino.h>

class MidiOut
{
public:
  void begin();

  void sendProgramChange(uint8_t program, uint8_t channel = 1);
  void sendControlChange(uint8_t cc, uint8_t value, uint8_t channel = 1);

private:
  HardwareSerial _serial = HardwareSerial(2);

  static constexpr uint8_t TX_PIN = 17;
};

#endif