# Delta Map: Upstream MeshCore vs Custom Wio Tracker Firmware

This document separates what likely already exists in upstream MeshCore from what appears to be extended or custom in the Wio Tracker L1 Pro firmware release.

## Legend

- **Baseline** — clearly supported by upstream MeshCore source/docs
- **Extended** — upstream has a foundation, but the release firmware appears to add more UI/workflow layers
- **Custom-only** — not obviously present upstream; likely specific to this custom firmware

## 1) Platform and board support

### Wio Tracker L1 board support
- **Status:** Baseline
- **Evidence upstream:** `boards/seeed-wio-tracker-l1.json`
- **Evidence firmware:** nRF52840 UF2/DFU images for Wio Tracker L1 variants
- **Conclusion:** no need to reverse-engineer board bring-up from scratch

### nRF52840 + SoftDevice BLE environment
- **Status:** Baseline
- **Evidence upstream:** nRF52 board support, SoftDevice config in board JSON, nRF52 BLE code paths
- **Conclusion:** reuse upstream patterns first

## 2) Core mesh / packets / contacts / channels

### Packet and mesh transport core
- **Status:** Baseline
- **Evidence upstream:** `Mesh.cpp`, `Packet.cpp`, `Dispatcher.cpp`
- **Conclusion:** should come directly from upstream design

### Contact discovery and advert parsing
- **Status:** Baseline
- **Evidence upstream:** `BaseChatMesh.cpp`, `ContactInfo.h`, advert helpers
- **Firmware overlap:** adverts, contacts, GPS in adverts, contact persistence clues
- **Conclusion:** do not reverse-engineer baseline parsing logic unless the custom firmware diverges

### Group channels and channel lookup
- **Status:** Baseline
- **Evidence upstream:** `ChannelDetails.h`, channel search APIs in `Mesh.h`
- **Firmware overlap:** `Channels`, private-channel UI strings
- **Conclusion:** channel plumbing is likely upstream; UI workflow is likely custom

## 3) Display and generic UI primitives

### Display drivers and screen abstraction
- **Status:** Baseline
- **Evidence upstream:** `src/helpers/ui/*`, `UIScreen.h`, multiple display drivers
- **Conclusion:** upstream already provides UI primitives and board display support

### Rich home carousel / screen suite
- **Status:** Extended / likely custom
- **Evidence firmware:** `Messages`, `Contacts`, `Channels`, `Adverts`, `Radio`, `Bluetooth`, `Sound`, `GPS`, `System`, `Tools`, plus `Home Radio`, `Home GPS`, `Home Time`, `Home Bluetooth`, `Home Sound`
- **Evidence upstream:** display framework exists, but I did not find matching high-level application UI strings in upstream scan
- **Conclusion:** reconstruct this as a custom app-layer shell built on upstream display/input primitives

## 4) Messaging UX

### Text message transport / ack behavior
- **Status:** Baseline
- **Evidence upstream:** `BaseChatMesh.cpp` handles text payloads, ACK behavior, flood/direct delivery
- **Conclusion:** messaging transport should be inferred from upstream, not binary archaeology

### Message threads, quick text, screen flows
- **Status:** Extended / likely custom
- **Evidence firmware:** `+Add quick text`, `-Remove quick text`, `Type quick text`, `Remove quick text`, `Messages cleared`, `No messages`
- **Evidence upstream:** no matching quick-text UI surfaced in quick scan
- **Conclusion:** likely custom UX layer on top of upstream text transport

## 5) Private channels UX

### Underlying channel capability
- **Status:** Baseline
- **Evidence upstream:** group channel types and channel helpers exist

### Invite/key share and join/create screens
- **Status:** Extended / likely custom
- **Evidence firmware:** `You got KEY to priv channel!`, `You got invite to priv channel...`, `+Join priv channel`, `+Create priv channel`
- **Conclusion:** reconstruct these as custom workflows over baseline channel features

## 6) Telemetry and repeater operations

### Sensor/telemetry data plumbing
- **Status:** Baseline
- **Evidence upstream:** `SensorManager`, CayenneLPP helpers, telemetry channels, GPS/environment data builders
- **Conclusion:** foundational telemetry protocol exists upstream

### Repeater login/admin/status orchestration
- **Status:** Extended / likely custom
- **Evidence firmware:** dense strings for `[Telemetry]`, `[Login]`, `[Owner]`, `[ACL]`, `[Nbr]`, retries, fallback modes, timeout handling, permissions masks
- **Evidence upstream:** telemetry primitives exist, but the surfaced repeater-admin workflow looks much richer in firmware strings
- **Conclusion:** very likely a custom orchestration/UI layer around upstream telemetry capabilities

## 7) BLE companion behavior

### BLE transport / companion protocol
- **Status:** Baseline
- **Evidence upstream:** BLE code, `docs/companion_protocol.md`, nRF52 BLE interfaces
- **Conclusion:** use upstream docs/code as the baseline for BLE transport behavior

### Companion-radio product behavior and UI exposure
- **Status:** Extended
- **Evidence firmware:** BLE build variants, Bluetooth status strings, home shortcut integration
- **Conclusion:** baseline protocol upstream; Wio-centric UX likely custom

## 8) Radio configuration UI

### Radio subsystem foundations
- **Status:** Baseline
- **Evidence upstream:** RadioLib helpers, board/radio abstractions
- **Conclusion:** base radio stack should be sourced from upstream

### Presets/custom-radio/settings UX
- **Status:** Extended
- **Evidence firmware:** `Radio Settings`, `Custom Radio`, `Radio Presets`, init-failure error strings
- **Conclusion:** likely custom configuration screens layered over upstream radio support

## 9) GPS subsystem

### GPS data and telemetry support
- **Status:** Baseline
- **Evidence upstream:** sensor/telemetry integration with GPS fields

### GPS menuing and hardware/data/settings views
- **Status:** Extended
- **Evidence firmware:** `GPS Data`, `GPS Hardware`, `GPS Settings`, `Show GPS data`, `Show GPS hardware`, `GPS Units`
- **Conclusion:** custom settings/UI layer very likely

## 10) Adverts

### Advert transport and data helpers
- **Status:** Baseline
- **Evidence upstream:** advert helpers, advert intervals/preferences in CLI/config structures

### Advert settings and user-facing flows
- **Status:** Extended
- **Evidence firmware:** `Adverts Settings`, `Advert sound ON/OFF`, `Advert sent!`, `Advert failed..`
- **Conclusion:** underlying capability upstream; polish/UI likely custom

## 11) Storage / persistence

### Basic persistence foundation
- **Status:** Baseline or partly baseline
- **Evidence upstream:** identity/key stores and helper storage patterns exist

### Rich history persistence and UI state
- **Status:** Extended / uncertain
- **Evidence firmware:** strings like `Filesystem mounted`, thread/channel history behavior implied by README and strings
- **Conclusion:** needs more work; likely custom persistence layer or an extended use of upstream storage

## 12) Tools / mini-apps

### Stopwatch / Countdown / Snake
- **Status:** Custom-only (for now)
- **Evidence firmware:** explicit strings present
- **Evidence upstream scan:** no obvious matches surfaced
- **Conclusion:** treat these as custom app modules until proven otherwise

## Highest-confidence reconstruction targets

These are the best candidates for custom-delta reconstruction:

1. **Home carousel and navigation shell**
2. **Messages / Contacts / Channels screen workflows**
3. **Quick-text editing and send flow**
4. **Private-channel invite/key UX**
5. **Repeater login/admin/status orchestration**
6. **Radio/GPS/System settings screens**
7. **Tools menu and mini-apps**

## What to reuse first

Before reverse-engineering more binary details, pull from upstream:

- mesh core and packet code
- contact/channel/advert primitives
- BLE companion protocol behavior
- nRF52/Wio board and display support
- telemetry base types and transport logic

## Recommended next implementation pass

Build the reconstruction around upstream MeshCore as the foundation, then implement custom delta modules for:

- `ui/home`
- `ui/messages`
- `ui/contacts`
- `ui/channels`
- `ui/settings`
- `features/telemetry/repeater_workflows`
- `features/tools`
