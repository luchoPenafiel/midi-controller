# NC MIDI Controller

A configurable MIDI footswitch controller built on the ESP32. Five footswitches send MIDI Control Change (CC) messages to control amps, effects, or any MIDI-compatible gear. Configuration is stored on-device and can be read or updated over USB serial.

## Features

- **5 footswitches** with dedicated buttons and status LEDs
- **Toggle behavior** — each press alternates between _on_ and _off_ action sets (non-scene footswitches)
- **Scenes** — optional per footswitch; at most one scene on at a time; switching runs other scenes’ `offActions` before the new scene’s `onActions`
- **Macro actions** — up to 10 CC messages per state (on/off) per footswitch
- **Persistent config** — settings saved in ESP32 NVS (survives power cycles)
- **USB configuration** — read and update the full device config over serial

## Hardware

| Component    | Board                                                |
| ------------ | ---------------------------------------------------- |
| MCU          | ESP32 DOIT DevKit V1                                 |
| Footswitches | 5 × momentary buttons (active low, internal pull-up) |
| Status LEDs  | 5 × GPIO-driven LEDs                                 |
| MIDI output  | UART2 @ 31250 baud (standard MIDI rate)              |

### Pin mapping

| Function | GPIO |
| -------- | ---- |
| Button 1 | 23   |
| Button 2 | 22   |
| Button 3 | 18   |
| Button 4 | 19   |
| Button 5 | 21   |
| LED 1    | 32   |
| LED 2    | 33   |
| LED 3    | 25   |
| LED 4    | 26   |
| LED 5    | 27   |
| MIDI TX  | 17   |

Connect the MIDI TX pin to your target device's MIDI IN (typically via a 5-pin DIN or TRS adapter circuit).

## Getting started

### Prerequisites

- [PlatformIO](https://platformio.org/) (CLI or VS Code extension)

### Build and upload

```bash
pio run
pio run --target upload
```

### Serial monitor

```bash
pio device monitor
```

Default baud rate: **115200** (USB serial for configuration).

## USB configuration protocol

Send commands as plain text lines over the USB serial port.

### Get current config

```
GET_CONFIG
```

Returns a JSON object with the full device configuration.

### Set config

```
SET_CONFIG {"midiChannel":1,"footswitches":[...]}
```

Responds with `OK` on success or `ERROR` on invalid JSON or out-of-range values.

### Config format

```json
{
  "midiChannel": 1,
  "footswitches": [
    {
      "name": "Boost",
      "isScene": false,
      "onActions": [
        { "cc": 38, "value": 127 },
        { "cc": 1, "value": 25 }
      ],
      "offActions": [{ "cc": 38, "value": 0 }]
    }
  ]
}
```

| Field          | Description                                    |
| -------------- | ---------------------------------------------- |
| `midiChannel`  | MIDI channel (1–16)                            |
| `footswitches` | Array of up to 5 footswitch configs            |
| `name`         | Label (max 32 characters)                      |
| `isScene`      | When true, footswitch participates in scene mutual exclusion (default `false`) |
| `onActions`    | CC messages sent when the footswitch turns on  |
| `offActions`   | CC messages sent when the footswitch turns off |

Each action requires `cc` and `value` in the range 0–127.

On first boot (or when no saved config exists), the device loads sensible defaults tailored for a multi-preset amp/effects setup (Boost, Lead, Post FX 1–3).

## Project structure

```
src/
  main.cpp                 # Entry point, hardware wiring
  Footswitch.cpp           # Button + LED + action orchestration
  FootswitchBank.cpp       # Scene selection and mutual exclusion
  ConfigurableMacroAction  # Toggle CC macro execution
  DeviceConfigManager.cpp  # NVS persistence and JSON parsing
  UsbConfigServer.cpp      # Serial config protocol
  MidiOut.cpp              # MIDI output over UART
include/                   # Headers
platformio.ini             # Board and dependency config
```

## TODO

- [ ] **Program Changes** — Only Control Changes (CC) are supported for now. Program Changes (PC) are not supported yet; this could be added in the future.

## Contributing

Contributions are welcome! Whether you want to fix a bug, improve documentation, add Program Change support, or extend the hardware layout — pull requests and issues are appreciated.

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/my-improvement`)
3. Commit your changes
4. Open a pull request against `main`

If you're planning a larger change, open an issue first so we can discuss the approach.

## Support

If you find this project useful, you can [buy me a coffee](https://buymeacoffee.com/lucianopend) ☕ — totally optional, but always appreciated.

## License

See the repository for license details.
