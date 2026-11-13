#include <Arduino.h>

#include "MidiOut.h"
#include "Footswitch.h"
#include "FootswitchBank.h"

#include "UsbConfigServer.h"
#include "DeviceConfigManager.h"

#include "ConfigurableMacroAction.h"

Button button1(23);
Button button2(22);
Button button3(18);
Button button4(19);
Button button5(21);

Led led1(32);
Led led2(33);
Led led3(25);
Led led4(26);
Led led5(27);

UsbConfigServer usbConfigServer;

DeviceConfigManager configManager;

MidiOut midi;

DeviceConfig *config;

ConfigurableMacroAction action1(midi);
ConfigurableMacroAction action2(midi);
ConfigurableMacroAction action3(midi);
ConfigurableMacroAction action4(midi);
ConfigurableMacroAction action5(midi);

Footswitch fs1(button1, led1, action1);
Footswitch fs2(button2, led2, action2);
Footswitch fs3(button3, led3, action3);
Footswitch fs4(button4, led4, action4);
Footswitch fs5(button5, led5, action5);

FootswitchBank footswitchBank;

void setup()
{
  configManager.begin();

  config = configManager.getConfig();

  usbConfigServer.begin(&configManager);

  midi.begin();

  action1.begin(config->footswitches[0]);
  action2.begin(config->footswitches[1]);
  action3.begin(config->footswitches[2]);
  action4.begin(config->footswitches[3]);
  action5.begin(config->footswitches[4]);

  footswitchBank.begin(config);

  footswitchBank.registerFootswitch(&fs1, 0);
  footswitchBank.registerFootswitch(&fs2, 1);
  footswitchBank.registerFootswitch(&fs3, 2);
  footswitchBank.registerFootswitch(&fs4, 3);
  footswitchBank.registerFootswitch(&fs5, 4);

  fs1.begin(&config->footswitches[0], &footswitchBank, 0);
  fs2.begin(&config->footswitches[1], &footswitchBank, 1);
  fs3.begin(&config->footswitches[2], &footswitchBank, 2);
  fs4.begin(&config->footswitches[3], &footswitchBank, 3);
  fs5.begin(&config->footswitches[4], &footswitchBank, 4);

  Serial.println("Start...");
}

void loop()
{
  usbConfigServer.loop();

  footswitchBank.update();
}
