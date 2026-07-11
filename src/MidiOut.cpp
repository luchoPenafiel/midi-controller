#include "MidiOut.h"

void MidiOut::begin()
{
  _serial.begin(31250, SERIAL_8N1, -1, TX_PIN);
}

void MidiOut::sendProgramChange(uint8_t program, uint8_t channel)
{
  _serial.write(0xC0 | ((channel - 1) & 0x0F));
  _serial.write(program);
}

void MidiOut::sendControlChange(uint8_t cc, uint8_t value, uint8_t channel)
{
  _serial.write(0xB0 | ((channel - 1) & 0x0F));
  _serial.write(cc);
  _serial.write(value);
}