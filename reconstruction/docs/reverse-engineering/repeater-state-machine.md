# Repeater Workflow State Machine

This document reconstructs the likely repeater login and telemetry workflow from firmware strings.

## Evidence highlights

Observed strings strongly imply:
- discovery-driven repeater entry point
- login required / login in progress / login fail / login timeout states
- multiple send modes: primary, direct, flood, fallback, legacy
- async tagged request/response handling
- follow-up retry scheduling
- separate actions for status, telemetry, owner info, ACL, neighbours

## Reconstructed state machine

### 1) Discovery
Entry points:
- `Discover Repeaters`
- repeater list inside contacts/repeater tabs

Likely transitions:
- idle -> scanning
- scanning -> repeater list updated live
- scanning -> no repeaters found
- select repeater -> repeater detail screen

### 2) Repeater detail
Likely data shown:
- repeater name
- maybe signal/path/range info
- login status
- available actions

Transitions:
- detail -> login prompt
- detail -> request status
- detail -> request telemetry
- detail -> owner / ACL / neighbours requests

### 3) Login
Evidence:
- `Login...`
- `Login in progress`
- `Login required`
- `Login failed`
- `Login timeout`
- `LOGIN OK`
- `LOGIN FAIL`

Likely transitions:
- idle -> login prompt
- submit password -> pending login
- pending login -> success / fail / timeout
- success -> unlocked action set

### 4) Request dispatch
Evidence shows multiple route strategies:
- primary
- direct
- flood
- flood-fallback
- legacy

Likely logic:
1. choose best route
2. send request tagged with transaction id
3. mark request pending in UI state
4. if no response, try fallback mode
5. on response, decode payload and update UI

### 5) Response families
Distinct operations likely mapped to different screens/panels:
- status
- telemetry
- owner info
- access list
- neighbours

### 6) Retry/follow-up system
Strings imply delayed follow-ups and retry chains:
- `follow-up timeout, retry`
- delayed send for owner / ACL / neighbours
- masked follow-up telemetry requests

This suggests a request coordinator with:
- pending transaction table
- timeout deadlines
- retry counter / route mode escalation
- response correlation by tag

## Suggested UI-facing repeater state

Minimal useful state for porting:
- selected repeater id
- login_required
- login_in_progress
- login_ok
- telemetry_permissions mask
- current request kind
- current request pending flag
- last request tag
- last error / timeout state
- last response summary

## Porting recommendation

Treat repeater handling as a dedicated adapter/service, not just button handlers in the UI.

Recommended split:
- UI screen(s): discovery, detail, result views
- repeater service: login + request + timeout/retry orchestration
- MeshCore adapter: actual send/request hooks into 1.15 core
