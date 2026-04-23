# Implementation Notes

This directory has moved from pure reverse-engineering into early 1.15 port scaffolding.

## Implemented first-pass pieces

- `invite_parser`: parses upstream-style `meshcore://channel/add?...` invites
- `thread_store`: minimal in-memory unified thread/message model for DM + channel UI
- `repeater_service`: result-model holder for status/owner/ACL/neighbour flows
- `app_shell`: simple home-carousel screen ring

## What is still missing

- binding adapters to real MeshCore 1.15 APIs
- persistence for thread history and quick text
- payload decoding for repeater result views
- full screen implementations for messages/contacts/channels/settings
