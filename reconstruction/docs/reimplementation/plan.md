# Reimplementation Plan

## Goal
Create a clean, evidence-backed source tree that mirrors the major firmware subsystems without pretending to restore the original proprietary/custom source verbatim.

## Phase 1
- boot/platform skeleton
- UI shell skeleton
- subsystem boundaries matching recovered architecture
- artifact and note preservation

## Phase 2
- message/contact/channel models
- settings/storage abstraction
- telemetry protocol notes and stub transport
- BLE/GPS/radio interface surfaces

## Phase 3
- incremental behavior reimplementation
- hardware bring-up
- parity testing against observed firmware behavior
