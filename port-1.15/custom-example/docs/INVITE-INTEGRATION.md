# Invite Integration

The custom example now has an app-layer path to import upstream-style channel invites into real channel slots.

## Current behavior

- Parses `meshcore://channel/add?...` invite text through the overlay parser
- Converts the parsed 16-byte secret into a channel record
- Saves the channel using the existing `setChannel(...)` / `saveChannels()` path

## Why this is useful

This keeps invite import inside the custom example/app layer while reusing upstream MeshCore channel persistence and transport primitives.
