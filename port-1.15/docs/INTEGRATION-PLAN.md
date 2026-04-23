# Integration Plan

## Chosen MeshCore 1.15 seam

The best immediate integration point is the existing `examples/companion_radio/MyMesh` pattern.

Why:
- it already subclasses `BaseChatMesh`
- it already receives direct and channel messages through callbacks
- it already has persisted contacts/channels via `DataStoreHost`
- it already has a UI task abstraction (`AbstractUITask`)

## First binding plan

### Direct messages
Bind from:
- `onMessageRecv(...)`
- `onSignedMessageRecv(...)`

Into:
- `mc_overlay_receive_direct_message(...)`
- thread store updates

### Channel messages
Bind from:
- `onChannelMessageRecv(...)`

Into:
- `mc_overlay_receive_channel_message(...)`
- thread store updates

### Outgoing messages
Wrap calls to:
- `sendMessage(...)`
- `sendGroupMessage(...)`

With overlay-side local append calls so the UI history updates immediately.

### Private channel invites
Use:
- `mc_overlay_try_import_channel_invite(...)`

as the first parser path for DM text that matches upstream URL/QR style invites.

## Near-term target

Build a custom `MyMesh`-style companion variant for the Wio Tracker L1 Pro port that:
- feeds the overlay context from MeshCore callbacks
- exposes thread/channel/contact data through the overlay adapters
- lets the UI screens grow without baking app logic into core mesh classes
