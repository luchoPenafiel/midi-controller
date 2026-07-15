#include <Arduino.h>
#include "MidiOut.h"
#include "ActionManager.h"
#include "ToggleCCAction.h"
#include "ChangeCCAction.h"
#include "ToggleMacroAction.h"
#include "Footswitch.h"

int MIDI_CHANNEL = 1;

Button button1(18);
Button button2(19);

Led led1(25);
Led led2(26);

MidiOut midi;
ActionManager actionManager;

ToggleCCAction preFx1(midi, 37);  // Compressor. Olways on.
ToggleCCAction preFx2(midi, 38);  // OD
ToggleCCAction postFx1(midi, 39); // Modulation
ToggleCCAction postFx2(midi, 40); // Delay
ToggleCCAction postFx3(midi, 41); // Reverb
ChangeCCAction changeFx(midi, 1);

// Boost
ChangeCCAction enableFx1(midi, 38, 127);
ChangeCCAction disableFx1(midi, 38, 0);
ChangeCCAction setBoost(midi, 1, 25);
ToggleMacroAction preFx2Boost;

// Lead
ChangeCCAction enableFx2(midi, 38, 127);
ChangeCCAction disableFx2(midi, 38, 0);
ChangeCCAction setLeadGain(midi, 1, 64);
ToggleMacroAction preFx2LeadGain;

Footswitch fs1(button1, led1, preFx2Boost);
Footswitch fs2(button2, led2, preFx2LeadGain);

void setup()
{
  Serial.begin(115200);
  midi.begin();

  actionManager.assignAction(0, &preFx1);
  actionManager.assignAction(1, &preFx2);
  actionManager.assignAction(2, &postFx1);
  actionManager.assignAction(3, &postFx2);
  actionManager.assignAction(4, &postFx3);

  preFx2Boost.addOnAction(&enableFx1);
  preFx2Boost.addOnAction(&setBoost);
  preFx2Boost.addOffAction(&disableFx1);

  preFx2LeadGain.addOnAction(&enableFx2);
  preFx2LeadGain.addOnAction(&setLeadGain);
  preFx2LeadGain.addOffAction(&disableFx2);

  fs1.begin();
  fs2.begin();

  Serial.println("Start...");
}

void loop()
{
  fs1.update();
  fs2.update();
}
