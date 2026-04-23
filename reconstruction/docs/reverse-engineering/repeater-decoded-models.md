# Repeater Decoded Models

These are likely UI-facing decoded result models for repeater/admin screens.

## Status view
Likely data points:
- uptime
- RX/TX packet counts
- queue usage
- battery voltage
- last RSSI/SNR

These align with upstream `get stats` concepts in MeshCore docs.

## Telemetry view
Likely data points:
- GPS position or location access result
- environment data when permissions allow
- maybe battery/voltage if included in telemetry payload

## Owner view
Likely data points:
- owner name
- owner/admin info text

## ACL view
Likely data points:
- rows of identities or labels
- permission masks / access flags per row

## Neighbours view
Likely data points:
- neighbour/repeater labels
- RSSI/SNR or link quality
- maybe hop/path data

## Porting note
The exact wire payloads may differ, but the UI can still target stable decoded models like these and hide protocol differences behind a repeater adapter/service.
