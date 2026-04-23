# MeshCore 1.15 Port Workspace

This workspace is for porting the custom Wio Tracker L1 Pro UI layer onto upstream MeshCore 1.15.x.

## Strategy

- treat upstream MeshCore as the baseline
- keep custom UI logic in an overlay layer
- use adapter interfaces to isolate differences in contacts, channels, threads/history, telemetry, and settings persistence

## Intended layout

- `overlay/include/` — UI-facing adapter and model headers
- `overlay/src/ui/` — custom screen modules
- `overlay/src/services/` — thread store, repeater workflow, settings overlay, invite parsing
- `../reconstruction/` — reverse-engineering notes and derived models

## Immediate next steps

1. wire the adapter interfaces to real MeshCore 1.15 types
2. implement thread/history service over MeshCore message callbacks
3. implement private-channel invite parsing
4. implement repeater workflow service and decoded result models
5. attach UI screens to upstream `UIScreen`/display primitives
