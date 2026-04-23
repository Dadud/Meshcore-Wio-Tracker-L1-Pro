# Custom Example Status

A first custom app/example target now exists under `port-1.15/custom-example/`.

## What it is

This is a working-port scaffold copied from upstream `examples/companion_radio` and modified at the app layer only.

## Current custom behavior

The copied `MyMesh` now forwards:
- direct messages into `mc_overlay_receive_direct_message(...)`
- signed direct messages into `mc_overlay_receive_direct_message(...)`
- channel messages into `mc_overlay_receive_channel_message(...)`

This means the overlay thread/history model is now wired into real MeshCore-style callback flow at the example layer.

## What is still missing

- compile verification against MeshCore include paths/build system
- proper adapter bindings for contacts/channels/settings
- replacing stock UI task behavior with overlay-backed screens
- persistence for overlay thread/history state
- invite import wired into actual channel-add flow

## Why this matters

This is the first point where the port is no longer just notes and generic scaffolding — message callbacks from a real MeshCore app target are now being redirected into the custom overlay architecture.
