# Private Channel Flow

This document reconstructs the likely private-channel UX and data path.

## Evidence

Observed firmware strings:
- `You got KEY to priv channel!`
- `You got invite to priv channel. Select this line and press Enter`
- `+Join priv channel`
- `+Create priv channel`

Upstream MeshCore capabilities:
- `ChannelDetails` contains `mesh::GroupChannel` plus `name`
- `BaseChatMesh::addChannel(const char* name, const char* psk_base64)` exists
- `BaseChatMesh::getChannel()`, `setChannel()`, `findChannelIdx()` exist

## Likely interpretation

The underlying private-channel primitive likely already exists upstream via `addChannel(name, psk_base64)`.
The custom firmware appears to add a richer UI workflow for:
- creating a private channel
- receiving a private-channel invite/key in DM
- importing the key into the local channel list
- opening the join flow directly from a message line

## Likely data path

### Create private channel
1. user selects `+Create priv channel`
2. UI prompts for channel name and/or generates a secret
3. UI calls into baseline channel-add path
4. resulting channel can be shared as a key/invite string via DM

### Join private channel from explicit action
1. user selects `+Join priv channel`
2. UI prompts for invite/key text
3. UI decodes invite or accepts PSK-like input
4. UI calls `addChannel()` with decoded name/key material

### Join from DM invite
1. DM contains a recognizable invite/key payload
2. UI renders a message-line action hint:
   - `You got invite to priv channel. Select this line and press Enter`
3. selecting that line triggers import/join flow
4. successful import creates a channel entry and updates channel list

## Likely custom-only parts

Most likely custom delta:
- invite/key message detection in thread UI
- parsing/decoding invite payload text
- share/import affordances in channel and DM screens
- validation/error messaging around join/create flows

## Likely baseline parts

Probably upstream-backed:
- channel secret representation
- local joined-channel table
- channel search/matching primitives
- persistence of channel entries once added

## Porting recommendation

Treat private channels as a custom UI workflow over upstream channel primitives, not a custom cryptographic subsystem.

Recommended adapter additions:
- `joinPrivateChannelFromText(const char* invite_or_key)`
- `createPrivateChannel(const char* name, char* out_share_text, int out_len)`
- `detectPrivateChannelInvite(const char* message_text)`
