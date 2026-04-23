# Custom MyMesh Port Shape

This document captures the intended 1.15 integration path for the custom Wio Tracker UI.

## Chosen base

Use the architecture from:
- `meshcore-upstream/examples/companion_radio/MyMesh.h`
- `meshcore-upstream/examples/companion_radio/MyMesh.cpp`

Why:
- already subclasses `BaseChatMesh`
- already persists contacts/channels through `DataStoreHost`
- already receives direct and channel messages through the exact callback surface we need
- already has an `AbstractUITask` boundary for display/UI integration

## Intended wiring

### Direct messages
From:
- `onMessageRecv(...)`
- `onSignedMessageRecv(...)`

To:
- `CustomMeshPort::onDirectMessage(...)`
- `mc_overlay_receive_direct_message(...)`
- overlay thread store

### Channel messages
From:
- `onChannelMessageRecv(...)`

To:
- `CustomMeshPort::onChannelMessage(...)`
- `mc_overlay_receive_channel_message(...)`
- overlay thread store

### Invite import
From DM text inspection:
- `CustomMeshPort::tryImportInvite(...)`

To:
- `mc_overlay_try_import_channel_invite(...)`
- eventual channel add/create flow

## Practical next implementation step

Fork the companion_radio example into a custom variant and replace the stock queue/offline-message UI path with overlay-backed thread/history plumbing.
