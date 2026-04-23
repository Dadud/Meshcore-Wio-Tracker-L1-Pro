# Storage Clues

This document collects current evidence about custom persistence and likely storage structure.

## Current evidence

Firmware strings observed:
- `/channels2`
- `/contacts3`
- `Filesystem mounted`
- `Messages cleared`
- `Clear messages?`
- `Remove all messages?`
- `No messages`

Upstream MeshCore evidence:
- prefs are saved to files such as `/com_prefs` and historically `/node_prefs`
- `BaseChatMesh` provides `getBlobByKey()` / `putBlobByKey()` hooks
- upstream stores raw advert blobs keyed by contact public key
- LittleFS is used in at least some upstream targets

## Likely interpretation

The custom firmware probably uses a filesystem-backed custom storage layer for UI/history state.

### Strong hints
- `/channels2` and `/contacts3` look like versioned file or namespace identifiers
- `Filesystem mounted` suggests startup/init logging for an app-level storage subsystem
- message-clear strings imply explicit deletion/reset of history-backed data

## Most likely storage split

### Files or blobs likely used for baseline data
- contacts list or cached advert blobs
- channels list
- baseline prefs

### Files or blobs likely used for custom UI data
- thread index
- per-thread history pages
- quick texts
- unread/total counters
- repeater session metadata or cached responses

## Plausible design patterns

### Option A: versioned flat files
Examples:
- `/contacts3`
- `/channels2`
- `/messages*`
- `/quicktext*`

### Option B: key-value blob store plus a few files
Examples:
- contact/channel metadata in files
- per-contact advert or thread state in blob-keyed storage
- history chunks keyed by contact/channel identifiers

### Option C: hybrid
Most likely in practice:
- core prefs and tables in fixed files
- raw adverts and selected objects in blob store
- custom thread/history in separate files or chunk series

## Porting implication

For the 1.15 port, it is probably safer to recreate the custom UI persistence cleanly rather than trying to preserve the exact original on-disk format unless compatibility with existing stored history matters.
