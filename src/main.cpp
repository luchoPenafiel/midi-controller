#include <Arduino.h>
#include "Button.h"
#include "MidiOut.h"
#include "ActionManager.h"
#include "ToggleCCAction.h"
#include "ChangeCCAction.h"
#include "ToggleMacroAction.h"

int MIDI_CHANNEL = 1;

Button button1(18);
Button button2(19);

MidiOut midi;
ActionManager actionManager;

ToggleCCAction preFx1(midi, 37);
ToggleCCAction preFx2(midi, 38);
ToggleCCAction postFx1(midi, 39);
ToggleCCAction postFx2(midi, 40);
ToggleCCAction postFx3(midi, 41);
ChangeCCAction changeFx(midi, 1);

ChangeCCAction enableFx(midi, 39, 127);
ChangeCCAction disableFx(midi, 39, 0);

ChangeCCAction setBoost(midi, 1, 5);
ToggleMacroAction preFx2Boost;

ChangeCCAction setLeadGain(midi, 1, 100);
ToggleMacroAction preFx2LeadGain;

void setup()
{
  Serial.begin(115200);
  midi.begin();
  button1.begin();
  button2.begin();

  actionManager.assignAction(0, &preFx1);
  actionManager.assignAction(1, &preFx2);
  actionManager.assignAction(2, &postFx1);
  actionManager.assignAction(3, &postFx2);
  actionManager.assignAction(4, &postFx3);

  preFx2Boost.addOnAction(&enableFx);
  preFx2Boost.addOnAction(&setBoost);
  preFx2Boost.addOffAction(&disableFx);

  preFx2LeadGain.addOnAction(&enableFx);
  preFx2LeadGain.addOnAction(&setLeadGain);
  preFx2LeadGain.addOffAction(&disableFx);

  Serial.println("Start...");
}

void loop()
{
  button1.update();
  button2.update();

  if (button1.wasPressed())
  {
    preFx2Boost.execute();
  }

  if (button2.wasPressed())
  {
    preFx2LeadGain.execute();
  }
}
