#ifndef MESHCORE_OVERLAY_CONTEXT_H
#define MESHCORE_OVERLAY_CONTEXT_H

#include <stdint.h>
#include "meshcore/models/app_models.h"
#include "meshcore/models/history_models.h"
#include "meshcore/services/invite_parser.h"

/*
 * Lightweight port-layer context and entry points for binding the custom UI
 * overlay onto MeshCore 1.15 callback surfaces.
 */

typedef struct {
  uint8_t contact_prefix[6];
  char title[MC_MAX_THREAD_TITLE];
} mc_overlay_contact_ref_t;

typedef struct {
  uint8_t channel_index;
  char title[MC_MAX_THREAD_TITLE];
  bool is_private;
} mc_overlay_channel_ref_t;

void mc_overlay_init(void);
int mc_overlay_ensure_direct_thread(const mc_overlay_contact_ref_t* contact);
int mc_overlay_ensure_channel_thread(const mc_overlay_channel_ref_t* channel);
bool mc_overlay_receive_direct_message(const mc_overlay_contact_ref_t* contact, uint32_t timestamp, const char* text, bool acknowledged);
bool mc_overlay_receive_channel_message(const mc_overlay_channel_ref_t* channel, uint32_t timestamp, const char* text);
bool mc_overlay_send_direct_message(const mc_overlay_contact_ref_t* contact, uint32_t timestamp, const char* text);
bool mc_overlay_send_channel_message(const mc_overlay_channel_ref_t* channel, uint32_t timestamp, const char* text);
bool mc_overlay_try_import_channel_invite(const char* text, mc_channel_invite_t* out);

#endif
