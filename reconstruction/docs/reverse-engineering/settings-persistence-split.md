# Settings Persistence Split

This document separates likely upstream-backed settings from likely custom UI persistence.

## Likely upstream-backed settings

These likely map to MeshCore `NodePrefs`, sensor settings, or other existing upstream storage:

- radio frequency / SF / BW / CR / TX power
- telemetry policy toggles
- GPS enable/interval related settings
- device name
- BLE PIN / bluetooth-related baseline settings
- auto-add contact behavior
- repeat / routing-related core prefs

## Likely custom UI persistence

These are more likely owned by the custom UI layer and stored separately from baseline prefs:

- home shortcut visibility toggles
- quick text entries
- message thread unread counters
- thread ordering / recent-message metadata
- muted channel UI state
- screen lock / unlock UX state
- UI-specific display preferences not represented upstream

## Likely hybrid areas

Some settings may straddle both worlds:

- advert sound
- GPS display preferences versus GPS hardware enablement
- display wake-on-message behavior
- battery display mode / rounding

These may require either:
- extending upstream prefs, or
- storing custom overlays and translating them into core behavior where needed

## Porting recommendation

For MeshCore 1.15 porting:

1. bind baseline settings directly to upstream prefs APIs
2. keep custom UI state in a separate persistence namespace
3. avoid polluting core prefs with purely UI concerns unless upstream already has a natural field for them
