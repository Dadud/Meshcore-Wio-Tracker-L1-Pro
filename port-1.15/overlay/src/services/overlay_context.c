#include "meshcore/services/overlay_context.h"
#include "meshcore/services/thread_store.h"

#include <string.h>

static int find_direct_thread(const mc_overlay_contact_ref_t* contact) {
  mc_thread_summary_t thread;
  int i;
  for (i = 0; i < mc_thread_store_count(); ++i) {
    if (!mc_thread_store_get(i, &thread)) continue;
    if (thread.kind != MC_THREAD_DIRECT) continue;
    if (strncmp(thread.title, contact->title, sizeof(thread.title)) == 0) return i;
  }
  return -1;
}

static int find_channel_thread(const mc_overlay_channel_ref_t* channel) {
  mc_thread_summary_t thread;
  int i;
  for (i = 0; i < mc_thread_store_count(); ++i) {
    if (!mc_thread_store_get(i, &thread)) continue;
    if (thread.kind != MC_THREAD_CHANNEL) continue;
    if (strncmp(thread.title, channel->title, sizeof(thread.title)) == 0) return i;
  }
  return -1;
}

void mc_overlay_init(void) {
  mc_thread_store_init();
}

int mc_overlay_ensure_direct_thread(const mc_overlay_contact_ref_t* contact) {
  mc_thread_summary_t thread;
  int idx;
  if (!contact) return -1;
  idx = find_direct_thread(contact);
  if (idx >= 0) return idx;
  memset(&thread, 0, sizeof(thread));
  thread.kind = MC_THREAD_DIRECT;
  strncpy(thread.title, contact->title, sizeof(thread.title) - 1);
  return mc_thread_store_append_thread(&thread);
}

int mc_overlay_ensure_channel_thread(const mc_overlay_channel_ref_t* channel) {
  mc_thread_summary_t thread;
  int idx;
  if (!channel) return -1;
  idx = find_channel_thread(channel);
  if (idx >= 0) return idx;
  memset(&thread, 0, sizeof(thread));
  thread.kind = MC_THREAD_CHANNEL;
  thread.is_private = channel->is_private;
  strncpy(thread.title, channel->title, sizeof(thread.title) - 1);
  return mc_thread_store_append_thread(&thread);
}

bool mc_overlay_receive_direct_message(const mc_overlay_contact_ref_t* contact, uint32_t timestamp, const char* text, bool acknowledged) {
  mc_history_message_t msg;
  int idx = mc_overlay_ensure_direct_thread(contact);
  if (idx < 0 || !text) return false;
  memset(&msg, 0, sizeof(msg));
  msg.timestamp = timestamp;
  msg.outgoing = false;
  msg.acknowledged = acknowledged;
  strncpy(msg.sender, contact->title, sizeof(msg.sender) - 1);
  strncpy(msg.text, text, sizeof(msg.text) - 1);
  return mc_thread_store_append_message(idx, &msg);
}

bool mc_overlay_receive_channel_message(const mc_overlay_channel_ref_t* channel, uint32_t timestamp, const char* text) {
  mc_history_message_t msg;
  int idx = mc_overlay_ensure_channel_thread(channel);
  if (idx < 0 || !text) return false;
  memset(&msg, 0, sizeof(msg));
  msg.timestamp = timestamp;
  msg.outgoing = false;
  strncpy(msg.sender, channel->title, sizeof(msg.sender) - 1);
  strncpy(msg.text, text, sizeof(msg.text) - 1);
  return mc_thread_store_append_message(idx, &msg);
}

bool mc_overlay_send_direct_message(const mc_overlay_contact_ref_t* contact, uint32_t timestamp, const char* text) {
  mc_history_message_t msg;
  int idx = mc_overlay_ensure_direct_thread(contact);
  if (idx < 0 || !text) return false;
  memset(&msg, 0, sizeof(msg));
  msg.timestamp = timestamp;
  msg.outgoing = true;
  msg.pending = true;
  strncpy(msg.sender, "me", sizeof(msg.sender) - 1);
  strncpy(msg.text, text, sizeof(msg.text) - 1);
  return mc_thread_store_append_message(idx, &msg);
}

bool mc_overlay_send_channel_message(const mc_overlay_channel_ref_t* channel, uint32_t timestamp, const char* text) {
  mc_history_message_t msg;
  int idx = mc_overlay_ensure_channel_thread(channel);
  if (idx < 0 || !text) return false;
  memset(&msg, 0, sizeof(msg));
  msg.timestamp = timestamp;
  msg.outgoing = true;
  msg.pending = true;
  strncpy(msg.sender, "me", sizeof(msg.sender) - 1);
  strncpy(msg.text, text, sizeof(msg.text) - 1);
  return mc_thread_store_append_message(idx, &msg);
}

bool mc_overlay_try_import_channel_invite(const char* text, mc_channel_invite_t* out) {
  return mc_invite_parse_channel_url(text, out);
}
