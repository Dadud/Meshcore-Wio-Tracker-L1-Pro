# UI-to-Core Integration Seams

This document maps the reconstructed custom UI layer to likely upstream MeshCore integration points.

## Goal

For a forward port to MeshCore 1.15.x, the important question is not just what the UI looked like, but what services it expected from the core firmware.

## Likely seam categories

### 1) Contacts seam

### Upstream evidence
- `ContactInfo` structure in upstream MeshCore
- advert parsing and contact creation in `BaseChatMesh.cpp`

### What the custom UI likely needs
- enumerate contacts
- enumerate repeater/sensor/room subsets
- favorite flags / filters / sorting
- contact details (name, type, GPS, last seen)
- delete/clear conversation actions

### Porting implication
The custom UI should likely bind to upstream contact tables/models rather than duplicating storage.

## 2) Channels seam

### Upstream evidence
- `ChannelDetails` structure
- group channel search and matching in `Mesh.h`

### What the custom UI likely needs
- list joined channels
- channel unread counts
- private/public metadata
- create/join/remove/mute actions
- channel message history access
- private-key share/import hooks

### Porting implication
The UI probably needs adapters around upstream channel structures plus a custom persistence/read-state layer.

## 3) Messaging seam

### Upstream evidence
- text message receive/ack behavior in `BaseChatMesh.cpp`
- peer/group datagram transport in MeshCore core

### What the custom UI likely needs
- thread list model for DMs and channels
- message history retrieval windows
- unread/total counts
- compose/send hooks
- quick-text insertion support
- clear-history hooks

### Porting implication
Transport is likely upstream; the custom delta is the thread/history/UI layer around it.

## 4) Telemetry seam

### Upstream evidence
- telemetry helpers and CayenneLPP paths in upstream MeshCore
- sensor manager abstractions

### What the custom UI likely needs
- login state and permission mask visibility
- request-status/request-telemetry commands
- async response callbacks
- owner / ACL / neighbour request entry points
- repeater discovery results

### Porting implication
This is one of the most important custom seams. The port likely needs a thin adapter layer around 1.15 telemetry APIs so the custom repeater UI can remain mostly stable.

## 5) BLE / companion seam

### Upstream evidence
- companion protocol docs
- BLE transport support for nRF52

### What the custom UI likely needs
- bluetooth connected/disconnected state
- PIN/status display
- maybe host-input or companion-radio coordination

### Porting implication
Mostly baseline, but the UI may expect specific status surfaces.

## 6) Settings / persistence seam

### Upstream evidence
- upstream stores identity/keys/config in helper layers
- firmware strings show filesystem-backed persistence

### What the custom UI likely needs
- persisted home shortcut visibility
- quick-text storage
- message/channel history metadata
- settings for GPS/radio/display/sound/battery/system
- repeater login/session state or recent results

### Porting implication
A custom persistence layer may be needed even if the underlying filesystem/provider changes between 1.14 and 1.15.

## 7) UI runtime seam

### Upstream evidence
- `UIScreen` defines `render`, `handleInput`, and `poll`

### What the custom UI likely needs
- screen stack or carousel manager
- per-screen render + input + async poll callbacks
- timed redraw/update support

### Porting implication
This is promising: the custom UI can probably be rebuilt as a suite of screen objects over upstream display/input primitives.

## Most likely port strategy

1. keep MeshCore 1.15 core and board support as the base
2. recreate the custom UI as a separate app-layer module set
3. build adapters for:
   - contacts
   - channels
   - message threads/history
   - repeater telemetry actions
   - settings persistence
4. avoid patching deep core paths unless the 1.15 APIs are missing required hooks

## Highest-value adapters to design first

- `ui_contacts_adapter`
- `ui_channels_adapter`
- `ui_threads_adapter`
- `ui_repeater_adapter`
- `ui_settings_store`

These adapters should isolate most 1.14 -> 1.15 churn from the reconstructed custom UI.
