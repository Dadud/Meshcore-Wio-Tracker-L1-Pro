# Adapter Contracts for UI Porting

These adapter contracts define the likely seam between the reconstructed custom UI layer and the underlying MeshCore core.

## Why these adapters exist

The custom firmware appears to add a rich app-layer UI on top of baseline MeshCore capabilities. To port that UI onto MeshCore 1.15.x, the cleanest approach is to isolate core-version differences behind a small set of adapter interfaces.

## Adapter groups

### Contacts adapter
Supports:
- listing contacts/repeaters/rooms/sensors
- favorite toggle
- delete actions
- location and last-seen metadata

### Channels adapter
Supports:
- listing channels
- unread/muted/private metadata
- remove/mute actions
- private-key aware UI behavior

### Threads/history adapter
Supports:
- unified DM/channel thread summaries
- history retrieval windows
- send/clear operations
- unread and total counters

### Quick text adapter
Supports:
- listing quick-text entries
- add/remove flows
- insertion into compose UX

### Repeater/telemetry adapter
Supports:
- repeater state lookup
- login workflow
- request status / telemetry / owner info / ACL / neighbours

### Settings adapter
Supports:
- home shortcut visibility
- input filter settings
- advert sound
- GPS-enabled state
- persistence of UI preferences

## Evidence basis

These contracts are derived from:
- firmware strings in `notes/ui-strings.txt` and `notes/telemetry-strings.txt`
- workflow notes in `docs/reverse-engineering/ui-workflows.md`
- upstream MeshCore structures such as `ContactInfo`, `ChannelDetails`, and `UIScreen`

## Porting principle

The UI should depend on adapter contracts like these rather than directly binding to MeshCore internals. That should reduce churn when moving from a 1.14-era baseline to 1.15.x.
