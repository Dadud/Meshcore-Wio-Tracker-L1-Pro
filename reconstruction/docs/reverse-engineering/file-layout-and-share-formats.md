# Likely File Layout and Share Formats

This document captures the most plausible storage layout and channel-share formats based on upstream MeshCore docs plus recovered firmware strings.

## Likely file layout

### Strong clues
Recovered firmware strings:
- `/channels2`
- `/contacts3`
- `Filesystem mounted`

Upstream patterns:
- `/com_prefs`
- historical `/node_prefs`
- versioned filenames such as `/regions2`
- blob-style storage hooks via `getBlobByKey()` / `putBlobByKey()`

## Most likely local files

### Baseline-oriented files
- `/com_prefs` or equivalent prefs file
- `/contacts3` for contact table or cached contact metadata
- `/channels2` for joined channel table or channel metadata
- keyed blobs for raw advert packets by contact public key

### Custom UI files or namespaces
Most likely candidates:
- `/threads*` or equivalent thread index file
- `/messages*` or per-thread history chunks
- `/quicktext*`
- `/ui*` or similar UI settings overlay
- repeater cache / session artifacts (if persisted)

## Most likely persistence pattern

Most plausible design is hybrid:
- fixed files for tables/settings
- blob storage for key-addressed records
- append or chunk files for message history

## Private/public channel share formats

### Upstream confirmed formats
Companion and QR docs confirm channel sharing concepts like:
- channel name
- 16-byte channel secret
- URL/QR form such as:
  - `meshcore://channel/add?name=<name>&secret=<secret>`

### Likely custom firmware usage
The custom firmware likely supports one or more of:
- encoded private-channel invite text in DM
- displayed private key/share action in channel UI
- import-on-select flow from recognized message text

## Likely private-channel invite model

Most probable possibilities, in descending order:
1. a text representation close to `meshcore://channel/add?...`
2. a compact custom line carrying name + 16-byte secret
3. a UI-generated message wrapper around standard channel metadata

## Porting recommendation

For the 1.15 port:
- support a parser for `meshcore://channel/add?...` style invites first
- add a second parser path for any custom invite text discovered later
- do not block the port on exact invite-format parity if the underlying channel secret flow works
