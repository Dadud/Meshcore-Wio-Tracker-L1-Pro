# Repeater Response Surfaces

This document summarizes likely UI-visible repeater response categories.

## Evidence

Observed strings:
- `[Status] admin requestStatus sent=%s`
- `[Telemetry] requestTelemetry sent=%s mask=0x%02X`
- `[Telemetry] payload hex:`
- `[Owner] follow-up requestOwnerInfo sent=%s`
- `[ACL] follow-up requestAccessList sent=%s`
- `[Nbr] follow-up requestNeighbours sent=%s`
- corresponding retry/follow-up logs for each family

## Likely response families

### 1) Status view
Likely surface:
- repeater stats summary
- maybe uptime, routing/radio counters, or online/connection state

### 2) Telemetry view
Likely surface:
- location and environment data gated by permission mask
- possibly rendered from a binary telemetry payload (hence `payload hex` logs during debug)

### 3) Owner info view
Likely surface:
- repeater owner/admin information
- probably text-heavy details

### 4) Access-list view
Likely surface:
- list of identities/permissions or allowed nodes
- maybe a paged text/list screen

### 5) Neighbours view
Likely surface:
- nearby or linked nodes/repeaters
- likely a short list with signal/path-related details

## Architectural implication

These likely map cleanly to separate result panes or submenu screens under a repeater detail page.

Suggested UI breakdown:
- repeater detail overview
- status result screen
- telemetry result screen
- owner info screen
- access-list screen
- neighbours screen

## Porting recommendation

Keep the request coordinator separate from the view renderer:
- one service issues requests and tracks tags/timeouts
- separate result-formatting code converts replies into UI-facing models
- UI screens consume already-decoded or lightly wrapped result objects
