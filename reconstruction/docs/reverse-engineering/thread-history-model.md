# Thread and History Model

This document reconstructs the likely custom message/thread layer built on top of upstream MeshCore transport.

## Why this likely exists

Upstream MeshCore appears to provide message transport and callbacks, but not the richer persistent thread/history UX exposed by the custom firmware.

Evidence from firmware strings and prior README notes suggests:
- per-contact DM threads
- per-channel message history
- unread and total counters
- persisted history windows
- quick-text integration
- clear-history operations

## Reconstructed entities

### Thread summary
A unified UI object representing either:
- a direct-message thread with a contact
- a channel thread

Likely fields:
- thread kind (`direct` or `channel`)
- title/display name
- unread count
- total count
- muted flag
- private flag
- backing contact/channel reference
- last message timestamp

### Message entry
Likely fields:
- timestamp
- outgoing/incoming flag
- acknowledged flag for DMs
- sender display name
- text payload
- maybe delivery/retry markers

### Quick text entry
Likely fields:
- text
- enabled/in-use flag
- stable order index

## Likely storage behavior

Based on release notes and strings, the custom firmware probably maintains:

- a persisted index of threads
- persisted unread/total counters
- per-thread rolling message history
- RAM windows over a larger persisted history store

Previously documented limits from the release README suggest:
- DM active RAM window: ~20 messages
- Channel active RAM window: ~100 messages

That points to a design like:
- on-disk append-only or chunked message storage
- small in-memory recent-message cache per active thread
- lazy paging for older history

## Likely operations

### On incoming DM
1. upstream MeshCore callback receives text payload
2. custom layer resolves or creates DM thread
3. append message to persisted history
4. increment unread/total counters
5. update thread ordering / recent preview
6. trigger notification / wake screen depending on settings

### On incoming channel message
1. upstream group-message callback fires
2. resolve channel thread
3. append to channel history
4. increment unread/total if not currently focused
5. update list ordering and preview

### On opening thread
1. load recent message window into RAM
2. display history
3. mark unread count as read or partially read
4. allow compose / quick text / clear actions

### On sending message
1. compose text or select quick text
2. dispatch through upstream send API
3. append local outgoing entry immediately
4. mark ACK state later for DMs if supported

### On clear history
1. confirm via `Clear messages?` or `Remove all messages?`
2. delete or reset thread history store
3. reset unread/total counters
4. emit `Messages cleared`

## Likely persistence split

### Probably upstream-backed
- contact identity data
- joined channels
- transport/security material

### Probably custom-layer persisted
- thread index
- message history store
- unread counters
- quick texts
- muted state and UI sorting metadata

## Porting recommendation

Implement this as a separate `ui_threads_adapter` over MeshCore 1.15 callbacks:
- normalize incoming DM/channel messages into one thread model
- keep thread persistence independent from MeshCore core storage where possible
- isolate quick-text persistence in a custom store
