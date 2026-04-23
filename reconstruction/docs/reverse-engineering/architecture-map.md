# Recovered Architecture Map

This map is inferred from firmware strings, vector data, and release metadata. It is a working model for reconstruction, not ground truth source documentation.

## Platform

- MCU: **Nordic nRF52840**
- Firmware form factors seen in releases:
  - WioTrackerL1 companion radio BLE
  - WioTrackerL1 companion radio USB
  - WioTrackerL1Eink companion radio BLE
- Image style:
  - UF2 image for drag-and-drop flashing
  - Nordic DFU ZIP bundle for app update flows

## High-level subsystem map

### 1) Boot / startup / interrupts
Evidence:
- Cortex-M vector table present at image start
- reset/NMI/HardFault/SVCall/PendSV handlers visible in header

Likely responsibilities:
- MCU startup and runtime init
- interrupt registration
- scheduler or RTOS integration if present
- handoff to board/app initialization

### 2) UI shell / home carousel
Evidence:
- `Messages`, `Contacts`, `Channels`, `Adverts`, `Radio`, `Bluetooth`, `Sound`, `GPS`, `System`, `Tools`
- `Home Radio`, `Home GPS`, `Home Time`, `Home Bluetooth`, `Home Sound`

Likely responsibilities:
- top-level page navigation
- menu rendering
- selection state and shortcuts
- per-screen routing

### 3) Messaging / contacts / channels
Evidence:
- `Messages`, `Contacts`, `Channels`
- `+Add quick text`, `-Remove quick text`
- `+Join priv channel`, `+Create priv channel`
- `You got KEY to priv channel!`
- `Messages cleared`, `Clear messages?`
- paths like `/channels2`, `/contacts3`

Likely responsibilities:
- DM threads
- channel threads and membership
- quick-text templates
- private channel invitation/key flows
- persistent conversation storage

### 4) Telemetry / repeater operations
Evidence:
- dense `[Telemetry]`, `[Login]`, `[Owner]`, `[ACL]`, `[Nbr]` logs
- `Telemetry perms`, `Login required`, `Login timeout`, `Discover Repeaters`
- direct/flood/legacy/fallback patterns

Likely responsibilities:
- remote telemetry request/reply protocol
- repeater/admin login flow
- permission-masked data access
- owner info / ACL / neighbour discovery
- retry scheduling and follow-up state

### 5) Radio configuration
Evidence:
- `Radio Settings`, `Custom Radio`, `Radio Presets`
- `ERROR: radio init failed:`

Likely responsibilities:
- preset selection
- custom modulation parameter editing
- radio driver init
- repeat/repeater mode integration

### 6) GPS subsystem
Evidence:
- `GPS Data`, `GPS Hardware`, `GPS Settings`, `GPS Units`
- `GPS: Enabled`, `GPS: Disabled`, `No GPS data`
- key/value strings like `gps_interval`

Likely responsibilities:
- GPS device configuration
- fix/status reporting
- unit conversion and display
- periodic update scheduling

### 7) Bluetooth / BLE subsystem
Evidence:
- `Bluetooth`, `Home Bluetooth`
- `BLE: CONN_PARAM_UPDATE_REQUEST: ignoring stale callback for handle=0x%04X`
- companion radio BLE build variant names

Likely responsibilities:
- BLE connection state and pairing/session handling
- companion-device integration
- transport for UI/host/control interactions

### 8) Adverts subsystem
Evidence:
- `Adverts`, `Adverts Settings`, `Advert sound`, `Advert sound ON/OFF`
- `Advert sent!`, `Advert failed..`

Likely responsibilities:
- advert composition/transmission
- advert rate control
- sound/notification integration
- optional share-position behavior

### 9) Settings / system / storage
Evidence:
- `System`, `Display`, `Battery`, `Sound: %s`
- `Defaults restored`
- `Filesystem mounted`
- `Can't unlock mutex, was NULL`

Likely responsibilities:
- persistent config management
- filesystem-backed history/settings
- display and battery preferences
- synchronization around shared services/storage

### 10) Tools / mini-apps
Evidence:
- `Tools`
- `Stopwatch`, `Countdown Timer`, `Snake`
- `Discover Repeaters`

Likely responsibilities:
- lightweight app launcher
- timer/game screens
- diagnostics and discovery tools

## Likely codebase decomposition for reconstruction

A sane reimplementation split would be:

- `core/` — boot glue, runtime, scheduler wrappers, logging
- `platform/` — nRF52840 + Wio Tracker board support
- `storage/` — filesystem/config/history
- `ui/` — menu framework, widgets, navigation, text input
- `features/messaging/`
- `features/channels/`
- `features/contacts/`
- `features/telemetry/`
- `features/radio/`
- `features/gps/`
- `features/ble/`
- `features/adverts/`
- `features/tools/`

## Immediate unknowns

Still unresolved without deeper disassembly:
- exact SDK/toolchain
- RTOS presence and task model
- radio stack/library boundaries
- filesystem implementation details
- BLE service layout
- exact message storage schema
- crypto/key handling for private channels

## Reconstruction principle

Repopulate the repo as:
1. immutable captured artifacts,
2. evidence-backed notes,
3. clean reimplementation stubs,
4. explicit separation between observed behavior and inferred internals.
