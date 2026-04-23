![Meshcore Wio Tracker L1 Pro](<img/1.jpg>)

# Meshcore Wio Tracker L1 Pro

Dadud's fork of the Wio Tracker L1 Pro custom MeshCore firmware project.

## What this repo is

This repository currently serves two purposes:

1. **Firmware release / landing page** for the custom Wio Tracker L1 Pro build
2. **Reverse-engineering and reconstruction workspace** for understanding the custom UI layer so it can be ported forward onto newer MeshCore releases

This is **not currently the original full source tree** for the custom firmware.
The upstream release repo published firmware artifacts, while this fork is being used to document and reconstruct the custom UI/features needed for a future port to newer MeshCore versions.

## Project goal

The goal of this fork is to:

- preserve the released custom Wio Tracker L1 Pro firmware artifacts
- document the custom UI and workflow differences from upstream MeshCore
- reconstruct the UI layer and feature behavior
- make it easier to port those customizations onto newer upstream MeshCore releases such as 1.15.x

## Upstream and credits

This project stands on several layers of work:

### Original custom Wio Tracker L1 Pro firmware release repo
- **sosprz / Przemek S**
- Repo: <https://github.com/sosprz/Meshcore-Wio-Tracker-L1-Pro>
- Releases: <https://github.com/sosprz/Meshcore-Wio-Tracker-L1-Pro/releases>

This repo provided the published firmware releases and feature documentation for the custom Wio Tracker L1 Pro build.

### MeshCore upstream project
- **meshcore-dev and contributors**
- Repo: <https://github.com/meshcore-dev/MeshCore>

MeshCore provides the core mesh networking firmware, board support, packet/message logic, BLE companion support, telemetry foundations, and much of the platform baseline this custom firmware builds upon.

### Hardware platform
- **Seeed Studio**
- Wio Tracker L1 hardware platform used by this firmware

### This fork
- **Dadud**
- Fork used to preserve progress, analyze the firmware, and prepare a UI-forward port to newer MeshCore releases

If you benefit from the original custom firmware work, please support the original author where appropriate:

[![Buy Me a Coffee](https://img.buymeacoffee.com/button-api/?text=Buy%20me%20a%20coffee&emoji=☕&slug=przemeks&button_colour=ff8800&font_colour=000000&font_family=Lato&outline_colour=000000&coffee_colour=FFDD00)](https://buymeacoffee.com/przemeks)

## Download firmware

Latest known custom firmware releases:
- <https://github.com/sosprz/Meshcore-Wio-Tracker-L1-Pro/releases>

## Flashing

### UF2 drag-and-drop

1. Double-click the reset/reboot button to enter bootloader mode.
2. A USB drive should appear on your computer.
3. Copy the `.uf2` file onto the device.
4. The device should reboot automatically after the copy completes.

### Web flasher

You can also use the MeshCore web flasher and choose **Custom firmware**:
- <https://flasher.meshcore.co.uk>

## Custom firmware feature summary

Based on the published firmware behavior and release documentation, the custom UI layer includes features such as:

- home carousel pages for `Messages`, `Contacts`, `Channels`, `Adverts`, `Radio`, `Bluetooth`, `Sound`, `GPS`, `Time`, `System`, and `Tools`
- direct-message and channel messaging flows
- quick text shortcuts and text-entry UX
- private channel join/create/share flows
- contact tabs including favorites, repeaters, rooms, and sensors
- radio presets and custom radio configuration
- GPS, display, battery, sound, and system settings screens
- telemetry and repeater workflows
- utility tools including repeater discovery, stopwatch, countdown timer, sensors, and snake

## Reconstruction work in this fork

This fork now includes a `reconstruction/` workspace with:

- captured firmware artifacts from released builds
- UF2 extraction tooling
- binary notes, strings, vector-table observations, and subsystem clues
- recovered architecture and delta maps
- early scaffolding for a clean-room reconstruction of the custom UI layer

Useful files include:
- `reconstruction/docs/reverse-engineering/README.md`
- `reconstruction/docs/reverse-engineering/architecture-map.md`
- `reconstruction/docs/reverse-engineering/baseline-vs-custom.md`
- `reconstruction/docs/reverse-engineering/delta-map.md`
- `reconstruction/docs/reimplementation/custom-ui-modules.md`

## Current direction

The current working assumption is:

- **MeshCore upstream** should be treated as the baseline
- the **custom Wio Tracker L1 Pro UI/workflow layer** is the main thing to reconstruct and port
- the end goal is to carry those custom UI features forward onto newer MeshCore releases rather than trying to recover the exact original source verbatim

## Notes

- This repository should be honest about what is original source, what is recovered evidence, and what is clean-room reconstruction.
- Reverse-engineering notes are intended to help with compatibility, preservation, and forward-porting work.
- If original source for the custom UI layer becomes available, that should replace reconstruction wherever possible.
