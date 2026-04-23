#include "meshcore/services/thread_store.h"

#include <string.h>

static mc_thread_slot_t g_threads[MC_THREAD_STORE_MAX_THREADS];
static mc_history_message_t g_messages[MC_THREAD_STORE_MAX_MESSAGES];
static int g_thread_count;
static int g_message_count;

void mc_thread_store_init(void) {
  memset(g_threads, 0, sizeof(g_threads));
  memset(g_messages, 0, sizeof(g_messages));
  g_thread_count = 0;
  g_message_count = 0;
}

int mc_thread_store_count(void) {
  return g_thread_count;
}

bool mc_thread_store_get(int index, mc_thread_summary_t* out) {
  if (!out || index < 0 || index >= g_thread_count) return false;
  *out = g_threads[index].thread;
  return true;
}

int mc_thread_store_append_thread(const mc_thread_summary_t* thread) {
  if (!thread || g_thread_count >= MC_THREAD_STORE_MAX_THREADS) return -1;
  g_threads[g_thread_count].thread = *thread;
  g_threads[g_thread_count].first_message = g_message_count;
  g_threads[g_thread_count].message_count = 0;
  return g_thread_count++;
}

bool mc_thread_store_append_message(int thread_index, const mc_history_message_t* msg) {
  mc_thread_slot_t* slot;
  if (!msg || thread_index < 0 || thread_index >= g_thread_count || g_message_count >= MC_THREAD_STORE_MAX_MESSAGES) return false;
  slot = &g_threads[thread_index];
  g_messages[g_message_count++] = *msg;
  slot->message_count++;
  slot->state.total_count++;
  if (!msg->outgoing) slot->state.unread_count++;
  slot->state.last_message_timestamp = msg->timestamp;
  slot->thread.total_count = slot->state.total_count;
  slot->thread.unread_count = slot->state.unread_count;
  return true;
}

int mc_thread_store_get_messages(int thread_index, int offset, int max_count, mc_history_message_t* out) {
  mc_thread_slot_t* slot;
  int copied = 0;
  if (!out || thread_index < 0 || thread_index >= g_thread_count || max_count <= 0) return 0;
  slot = &g_threads[thread_index];
  if (offset < 0) offset = 0;
  while (offset + copied < slot->message_count && copied < max_count) {
    out[copied] = g_messages[slot->first_message + offset + copied];
    copied++;
  }
  return copied;
}

bool mc_thread_store_mark_read(int thread_index) {
  mc_thread_slot_t* slot;
  if (thread_index < 0 || thread_index >= g_thread_count) return false;
  slot = &g_threads[thread_index];
  slot->state.unread_count = 0;
  slot->thread.unread_count = 0;
  return true;
}

bool mc_thread_store_clear(int thread_index) {
  mc_thread_slot_t* slot;
  if (thread_index < 0 || thread_index >= g_thread_count) return false;
  slot = &g_threads[thread_index];
  slot->message_count = 0;
  slot->state.unread_count = 0;
  slot->state.total_count = 0;
  slot->thread.unread_count = 0;
  slot->thread.total_count = 0;
  return true;
}
