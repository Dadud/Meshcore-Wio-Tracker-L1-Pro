# Recovered UI Workflows

This document captures likely screen flows inferred from firmware strings. These are working reverse-engineering notes for porting the custom UI onto newer MeshCore releases.

## 1) Home carousel

### Evidence
- `Messages`, `Contacts`, `Channels`, `Adverts`, `Radio`, `Bluetooth`, `Sound`, `GPS`, `Time`, `System`, `Tools`
- `Home Radio`, `Home GPS`, `Home Time`, `Home Bluetooth`, `Home Sound`

### Likely flow
- device boots into a home carousel or paged home screen
- left/right or prev/next rotates between top-level modules
- a UI settings page controls whether shortcut pages for Radio/GPS/Time/Bluetooth/Sound are shown
- enter/select opens the selected module screen

### Porting note
This likely sits on top of upstream `UIScreen`-style input/render primitives and should be recreated as an app-layer router rather than patched into low-level display drivers.

## 2) Messages workflow

### Evidence
- `Messages`
- `No messages`
- `Messages cleared`
- `Clear messages?`
- `Remove all messages?`
- `Remove messages`
- `Quick text`
- `+Add quick text`
- `-Remove quick text`
- `Type quick text`
- `Remove quick text`

### Likely flow
1. open `Messages`
2. show thread list or recent-message preview
3. if empty, show `No messages`
4. selecting a thread opens message history
5. compose flow supports standard text entry plus quick-text shortcuts
6. quick-text management supports:
   - list existing quick texts
   - add new quick text
   - remove quick text
7. thread or global history can be cleared with confirmation dialogs

### Likely states
- thread list
- thread detail/history
- compose editor
- quick-text picker
- quick-text add editor
- quick-text remove chooser
- clear-history confirmation

## 3) Contacts workflow

### Evidence
- `Contacts`
- `No contacts`
- `Repeaters:`
- `Contacts Settings`
- `ContactSettings: autoadd_config=0x%02X`
- `Discover Repeaters`
- `contacts`
- `repeaters`

### Likely flow
1. open `Contacts`
2. show tabbed/grouped contact lists
3. tabs likely include normal contacts and repeaters at minimum
4. if empty, show `No contacts`
5. selected contact opens actions like DM, telemetry, favorite, clear/delete
6. settings submenu exposes auto-add filters and related behavior
7. repeater discovery can be launched from tools or repeater-specific views

### Likely states
- contacts list
- repeater list
- contact action menu
- contacts settings
- repeater discovery results

## 4) Channels workflow

### Evidence
- `Channels`
- `Channels (%d)`
- `+Join priv channel`
- `+Create priv channel`
- `You got KEY to priv channel!`
- `You got invite to priv channel. Select this line and press Enter`
- `/channels2`

### Likely flow
1. open `Channels`
2. list channels with unread counts
3. action items for joining/creating private channels appear in the list or menu
4. DM-delivered private key/invite lines can trigger channel join flow
5. selected channel opens history view and actions such as mute, clear, remove, or share key

### Likely states
- channel list
- channel history
- channel actions menu
- private-channel join flow
- private-channel create flow
- invite/key-driven import flow

## 5) Settings workflow

### Evidence
- `Display`, `Radio`, `Bluetooth`, `Sound`, `System`, `Battery`
- `Radio Settings`, `Custom Radio`, `Radio Presets`
- `GPS Data`, `GPS Hardware`, `GPS Settings`, `Show GPS data`, `Show GPS hardware`, `GPS Units`
- `Sound: %s`
- `GPS: Enabled`, `GPS: Disabled`
- `Advert sound ON`, `Advert sound OFF`

### Likely flow
`System` acts as the umbrella menu, branching into grouped settings pages:
- UI/display settings
- radio settings and custom radio editor
- bluetooth settings/status
- sound settings
- GPS settings/data/hardware pages
- battery settings

### Likely states
- system root menu
- display submenu
- radio presets list
- custom radio editor
- bluetooth status/config
- sound level cycling screen
- GPS summary/data/hardware/settings pages
- battery settings page

## 6) Telemetry / repeater workflow

### Evidence
- `Telemetry`
- `Repeater`
- `Login`
- `Login...`
- `Login in progress`
- `Login required`
- `Login failed`
- `Login timeout`
- `Telemetry perms`
- `Request telemetry`
- `Discover Repeaters`
- rich log strings for status/telemetry/owner/ACL/neighbour follow-ups and retries

### Likely flow
1. discover repeaters
2. select repeater from list
3. open repeater detail/stats screen
4. if needed, prompt login
5. after login, offer actions:
   - request status
   - request telemetry
   - request owner info
   - request access list
   - request neighbours
6. asynchronous follow-up and retry logic updates the UI with success/failure/timeout states

### Likely states
- repeater discovery scan
- repeater list
- repeater detail/stats
- login prompt/input
- login pending state
- telemetry/status request pending state
- response display / failure display

## 7) Tools workflow

### Evidence
- `Discover Repeaters`
- `Stopwatch`
- `Countdown Timer`
- `Snake`

### Likely flow
Tools is a simple launcher menu for small applets and utility flows. `Discover Repeaters` may bridge back into telemetry/contact/repeater screens.

## Overall pattern

The custom firmware appears to add a fairly rich app-layer screen graph on top of baseline MeshCore transport, contact, channel, advert, BLE, and telemetry capabilities.
