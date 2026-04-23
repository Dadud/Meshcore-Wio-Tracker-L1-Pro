# Baseline vs Custom Strategy

## Working assumption

This firmware should be treated as:

- **Baseline:** upstream `meshcore-dev/MeshCore` around the 1.14.x era
- **Custom layer:** Wio Tracker L1 Pro UI / companion-radio behavior / added workflows and polish

## Why this is the right approach

The upstream MeshCore repo already contains:

- Wio Tracker L1 board support (`boards/seeed-wio-tracker-l1.json`)
- nRF52840 support
- companion protocol docs
- channel/message handling
- advert handling
- telemetry helpers
- BLE support on nRF52

That means we should avoid reverse-engineering anything that is already visible in upstream source.

## Likely baseline areas

Probably mostly reusable from upstream:
- packet and mesh core logic
- channel cryptography / hashing
- advert packet handling
- companion protocol framing
- base telemetry transport
- NRF52 board abstractions
- settings/storage primitives already present upstream

## Likely custom/delta areas

Most likely worth reverse-engineering or reconstructing:
- richer on-device UI shell / home carousel
- message/contact/channel screens and flows
- quick text UX
- private channel invite/key UX
- repeater login/status/admin flows
- tools screens (`Stopwatch`, `Countdown Timer`, `Snake`)
- Wio-specific display/input polish
- expanded telemetry/repeater orchestration

## Practical plan

1. Read upstream MeshCore source first for each subsystem
2. Mark what already exists upstream
3. Reverse-engineer only firmware-visible behavior not explained by upstream
4. Rebuild the repo as:
   - imported/referenced upstream baseline knowledge
   - documented custom delta
   - clean-room reimplementation of missing custom layers
