# Meshcore Wio Tracker L1 Pro Reconstruction

This workspace is for reverse-engineering and clean-room reconstruction of the custom Wio Tracker L1 Pro firmware releases.

## What we have

Artifacts captured from release `v1.14.1.73`:

- `artifacts/WioTrackerL1_companion_radio_ble-v1.14.1.73-7d24489f.uf2`
- `artifacts/WioTrackerL1_companion_radio_ble-v1.14.1.73-7d24489f.bin` (UF2-extracted raw app image)
- `artifacts/extracted_zip/firmware.bin` (Nordic DFU payload)
- `artifacts/extracted_zip/firmware.dat`
- `artifacts/extracted_zip/manifest.json`

## Confirmed facts

- Target family: **Nordic nRF52840**
- UF2 app base address: **0x027000**
- Raw image type: **ARM Cortex-M firmware**
- The UF2-derived BIN is slightly larger than the DFU `firmware.bin` because the UF2 payload includes padded/extra block coverage.

## What is recoverable

Likely recoverable:
- strings and UI text
- subsystem boundaries
- function layout
- protocol clues
- enough behavior to reimplement modules

Not realistically recoverable:
- original comments
- original symbol names
- original source tree
- exact source files

## Recommended workflow

1. Keep original artifacts immutable under `artifacts/`
2. Extract strings and feature clues into `notes/`
3. Load the raw BIN into a proper ARM reverse-engineering tool
4. Build a documented reconstruction in a fresh `src/` tree
5. Mark clearly what is observed, inferred, and reimplemented

## Immediate next steps

- Produce a richer categorized strings dump
- Map vector table and likely memory layout
- Set up a Ghidra project or another disassembler outside this repo
- Start subsystem notes for UI, radio, GPS, BLE, telemetry, storage
