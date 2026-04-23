# Custom UI Modules

This document maps firmware-visible features to reconstructed custom UI modules.

## Home
Evidence:
- `Messages`, `Contacts`, `Channels`, `Adverts`, `Radio`, `Bluetooth`, `Sound`, `GPS`, `System`, `Tools`
- `Home Radio`, `Home GPS`, `Home Time`, `Home Bluetooth`, `Home Sound`

Responsibilities:
- home carousel
- shortcut visibility/toggles
- top-level routing to feature screens

## Messages
Evidence:
- `Messages`
- `No messages`
- `Messages cleared`
- `Clear messages?`
- `+Add quick text`
- `-Remove quick text`
- `Type quick text`
- `Remove quick text`

Responsibilities:
- thread list / message preview
- compose flow
- quick text management
- clear-history actions

## Contacts
Evidence:
- `Contacts`
- `Contacts Settings`
- `Repeaters:`
- `No contacts`

Responsibilities:
- contact/favorites/repeater tabs
- contact actions
- contact settings / sorting / filters

## Channels
Evidence:
- `Channels`
- `Channels (%d)`
- `+Join priv channel`
- `+Create priv channel`
- `You got KEY to priv channel!`
- `You got invite to priv channel...`

Responsibilities:
- channel list and unread indicators
- private channel create/join flows
- private key/invite handling
- clear/remove/mute actions

## Settings
Evidence:
- `Display`
- `Radio`
- `Bluetooth`
- `Sound`
- `System`
- `Battery`
- `GPS Data`
- `GPS Hardware`
- `GPS Settings`
- `Radio Settings`
- `Custom Radio`
- `Radio Presets`

Responsibilities:
- grouped settings screens
- radio/gps/display/sound/battery/system forms
- persistence hooks

## Shared models
- quick text entries
- thread summaries
- repeater state/actions
