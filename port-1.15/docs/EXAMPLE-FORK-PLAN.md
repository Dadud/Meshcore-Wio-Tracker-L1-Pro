# Example Fork Plan

The cleanest path is to fork the upstream `examples/companion_radio` example into a custom app/example target while leaving MeshCore core untouched.

## Keep upstream core unchanged
Do not modify:
- `src/`
- `helpers/` shared core logic
- packet/mesh/radio internals

## Fork at the example/app layer
Use `examples/companion_radio` as the base and replace or augment:
- `MyMesh.*`
- `UITask.*`
- app-specific message/thread handling
- app-specific settings/history persistence

## Planned custom replacements
- stock queue/offline message pipeline -> overlay thread/history service
- stock/basic UI task -> custom app shell + custom screens
- channel invite handling -> overlay invite parser
- repeater admin flows -> overlay repeater service

## Proposed staged migration
1. clone companion_radio into a custom example target
2. compile with minimal behavioral changes
3. route message callbacks into overlay context
4. replace preview/list UI with overlay-backed thread model
5. add channel invite import
6. add repeater screens and settings overlay
