#include "DeviceConfigManager.h"

#include <ArduinoJson.h>

void DeviceConfigManager::begin()
{
    preferences.begin("device-config", false);
    // preferences.clear();

    load();
}

DeviceConfig *DeviceConfigManager::getConfig()
{
    return &config;
}

void DeviceConfigManager::save()
{
    preferences.putBytes(
        "config",
        &config,
        sizeof(DeviceConfig));
}

static bool parseActions(
    JsonArray actions,
    MidiCCAction *target,
    uint8_t *count)
{
    if (actions.isNull())
    {
        return false;
    }

    if (actions.size() > MAX_ACTIONS_PER_STATE)
    {
        return false;
    }

    for (size_t i = 0; i < actions.size(); i++)
    {
        JsonObject action = actions[i];

        if (
            !action["cc"].is<int>() ||
            !action["value"].is<int>())
        {
            return false;
        }

        int cc = action["cc"];
        int value = action["value"];

        if (
            cc < 0 || cc > 127 ||
            value < 0 || value > 127)
        {
            return false;
        }

        target[i] = {
            static_cast<uint8_t>(cc),
            static_cast<uint8_t>(value)};
    }

    *count = actions.size();

    return true;
}

bool DeviceConfigManager::setConfigFromJson(
    const String &json)
{
    JsonDocument doc;

    if (deserializeJson(doc, json))
    {
        return false;
    }

    if (!doc["midiChannel"].is<int>())
    {
        return false;
    }

    int midiChannel = doc["midiChannel"];

    if (midiChannel < 1 || midiChannel > 16)
    {
        return false;
    }

    JsonArray footswitches =
        doc["footswitches"].as<JsonArray>();

    if (
        footswitches.isNull() ||
        footswitches.size() > MAX_FOOTSWITCHES)
    {
        return false;
    }

    DeviceConfig newConfig;

    memset(
        &newConfig,
        0,
        sizeof(newConfig));

    newConfig.midiChannel =
        static_cast<uint8_t>(midiChannel);

    for (
        size_t i = 0;
        i < footswitches.size();
        i++)
    {
        JsonObject fs = footswitches[i];

        const char *name = fs["name"];

        if (
            name == nullptr ||
            strlen(name) >= MAX_NAME_LENGTH)
        {
            return false;
        }

        strncpy(
            newConfig.footswitches[i].name,
            name,
            MAX_NAME_LENGTH - 1);

        newConfig.footswitches[i].isScene = false;

        if (fs["isScene"].is<bool>())
        {
            newConfig.footswitches[i].isScene =
                fs["isScene"].as<bool>();
        }

        if (!parseActions(
                fs["onActions"].as<JsonArray>(),
                newConfig.footswitches[i].onActions,
                &newConfig.footswitches[i].onActionCount))
        {
            return false;
        }

        if (!parseActions(
                fs["offActions"].as<JsonArray>(),
                newConfig.footswitches[i].offActions,
                &newConfig.footswitches[i].offActionCount))
        {
            return false;
        }
    }

    config = newConfig;

    save();

    return true;
}

void DeviceConfigManager::load()
{
    size_t size =
        preferences.getBytesLength(
            "config");

    if (size == sizeof(DeviceConfig))
    {
        preferences.getBytes(
            "config",
            &config,
            sizeof(DeviceConfig));

        return;
    }

    setDefaults();

    save();
}

void DeviceConfigManager::setDefaults()
{
    memset(
        &config,
        0,
        sizeof(DeviceConfig));

    config.midiChannel = 1;

    // --------------------
    // Footswitch 1 - Boost
    // --------------------
    strcpy(config.footswitches[0].name, "Boost");
    config.footswitches[0].onActions[0] = {38, 127};
    config.footswitches[0].onActions[1] = {1, 25};
    config.footswitches[0].onActionCount = 2;
    config.footswitches[0].offActions[0] = {38, 0};
    config.footswitches[0].offActionCount = 1;

    // --------------------
    // Footswitch 2 - Lead
    // --------------------

    strcpy(config.footswitches[1].name, "Lead");

    config.footswitches[1].onActions[0] =
        {
            38,
            127};

    config.footswitches[1].onActions[1] =
        {
            1,
            64};

    config.footswitches[1].onActionCount = 2;

    config.footswitches[1].offActions[0] =
        {
            38,
            0};

    config.footswitches[1].offActionCount = 1;

    // --------------------
    // Footswitch 3
    // --------------------

    strcpy(
        config.footswitches[2].name,
        "Post FX 1");

    config.footswitches[2].onActions[0] =
        {
            39,
            127};

    config.footswitches[2].onActionCount = 1;

    config.footswitches[2].offActions[0] =
        {
            39,
            0};

    config.footswitches[2].offActionCount = 1;

    // --------------------
    // Footswitch 4
    // --------------------

    strcpy(
        config.footswitches[3].name,
        "Post FX 2");

    config.footswitches[3].onActions[0] =
        {
            40,
            127};

    config.footswitches[3].onActionCount = 1;

    config.footswitches[3].offActions[0] =
        {
            40,
            0};

    config.footswitches[3].offActionCount = 1;

    // --------------------
    // Footswitch 5
    // --------------------

    strcpy(
        config.footswitches[4].name,
        "Post FX 3");

    config.footswitches[4].onActions[0] =
        {
            41,
            127};

    config.footswitches[4].onActionCount = 1;

    config.footswitches[4].offActions[0] =
        {
            41,
            0};

    config.footswitches[4].offActionCount = 1;
}