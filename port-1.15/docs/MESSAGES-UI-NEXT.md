# Messages UI Next Slice

This slice keeps MeshCore core untouched and builds message-list behavior entirely in the overlay/app layer.

## Added
- `messages_list_view.h`
- `messages_list_view.c`

## Purpose
Provide a minimal overlay-backed thread list view over `mc_thread_store_*` so the custom example can start replacing stock preview/queue behavior with a real thread-oriented UI model.

## Next bind point
Use this from the custom UITask or a replacement screen class to:
- refresh visible thread summaries
- move selection up/down
- open the selected thread detail view later
