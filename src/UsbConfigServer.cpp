#include "UsbConfigServer.h"

void UsbConfigServer::begin(
    DeviceConfigManager *config)
{
  Serial.begin(115200);

  inputBuffer.reserve(4096);

  configManager = config;

  Serial.println("USB Config Server Ready");
}

void UsbConfigServer::loop()
{
  while (Serial.available())
  {
    char c = Serial.read();

    if (c == '\n')
    {
      inputBuffer.trim();

      if (inputBuffer.length() > 0)
      {
        processCommand(
            inputBuffer);
      }

      inputBuffer = "";
    }
    else
    {
      inputBuffer += c;
    }
  }
}

void UsbConfigServer::processCommand(
    const String &command)
{
  if (command == "GET_CONFIG")
  {
    sendConfig();
    return;
  }

  if (command.startsWith("SET_CONFIG "))
  {
    String json = command.substring(
        String("SET_CONFIG ").length());

    if (configManager->setConfigFromJson(json))
    {
      Serial.println("OK");
    }
    else
    {
      Serial.println("ERROR");
    }

    return;
  }

  Serial.println(
      "UNKNOWN_COMMAND");
}

void UsbConfigServer::sendConfig()
{
  DeviceConfig *config =
      configManager->getConfig();

  Serial.print("{");
  Serial.print("\"midiChannel\":");
  Serial.print(config->midiChannel);
  Serial.print(",\"footswitches\":[");

  for (
      uint8_t i = 0;
      i < MAX_FOOTSWITCHES;
      i++)
  {
    if (i > 0)
    {
      Serial.print(",");
    }

    sendFootswitchConfig(config->footswitches[i]);
  }

  Serial.println("]}");
}

void UsbConfigServer::sendFootswitchConfig(
    FootswitchConfig &footswitch)
{
  Serial.print("{");
  Serial.print("\"name\":\"");
  Serial.print(footswitch.name);
  Serial.print("\",\"isScene\":");
  Serial.print(footswitch.isScene ? "true" : "false");
  Serial.print(",\"onActions\":[");

  for (
      uint8_t i = 0;
      i < footswitch.onActionCount;
      i++)
  {
    if (i > 0)
    {
      Serial.print(",");
    }

    Serial.print("{");
    Serial.print("\"cc\":");
    Serial.print(footswitch.onActions[i].cc);
    Serial.print(",\"value\":");
    Serial.print(footswitch.onActions[i].value);
    Serial.print("}");
  }

  Serial.print("],\"offActions\":[");

  for (
      uint8_t i = 0;
      i < footswitch.offActionCount;
      i++)
  {
    if (i > 0)
    {
      Serial.print(",");
    }

    Serial.print("{");
    Serial.print("\"cc\":");
    Serial.print(footswitch.offActions[i].cc);
    Serial.print(",\"value\":");
    Serial.print(footswitch.offActions[i].value);
    Serial.print("}");
  }

  Serial.print("]}");
}