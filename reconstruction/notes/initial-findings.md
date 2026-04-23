# Initial Findings

## Release examined

- Repo: `sosprz/Meshcore-Wio-Tracker-L1-Pro`
- Asset: `WioTrackerL1_companion_radio_ble-v1.14.1.73-7d24489f.uf2`
- Companion DFU bundle also captured from matching release ZIP

## Binary facts

- UF2 family: Nordic NRF52840
- UF2 start address: `0x027000`
- Raw firmware reports as ARM Cortex-M
- Initial stack pointer: `0x20040000`
- Reset vector: `0x000A6A9C`
- NMI: `0x000A6ADC`
- HardFault: `0x000A7F0C`
- SVCall: `0x000A6A18`
- PendSV: `0x000A6A38`

## File sizes

- UF2-derived raw BIN: `673536` bytes
- DFU `firmware.bin`: `673348` bytes
- Difference: `188` bytes

The size mismatch suggests the UF2 payload contains alignment padding or extra covered bytes not present in the Nordic DFU BIN.

## Strings that confirm feature set

Observed directly in the binary:

- `Messages`
- `Contacts`
- `Channels`
- `Adverts`
- `Radio`
- `Bluetooth`
- `Sound`
- `GPS`
- `System`
- `Tools`
- `+Add quick text`
- `-Remove quick text`
- `+Join priv channel`
- `+Create priv channel`
- `Discover Repeaters`
- `Countdown Timer`
- `Stopwatch`
- `Snake`

## Telemetry clues

Observed log strings suggest a fairly structured telemetry/repeater workflow:

- request / reply flow
- permission masks
- legacy + direct + flood sending modes
- login retries / follow-up logic
- repeater-specific status requests

## Likely subsystems

- Home UI / menu system
- Messaging + channel storage
- BLE companion radio integration
- GPS configuration + data view
- Telemetry / repeater operations
- adverts subsystem
- settings / persistence
- lightweight apps/tools (snake, timer, stopwatch)

## Constraints

This is reverse-engineering, not source restoration. Any repopulated repo should be honest about reconstructed vs reimplemented code.
