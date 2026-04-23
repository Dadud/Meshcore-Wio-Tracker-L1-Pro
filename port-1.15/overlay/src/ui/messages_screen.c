#include "meshcore/services/thread_store.h"

/* Minimal messages screen helpers for the first 1.15 port slice. */

int mc_messages_screen_thread_count(void) {
  return mc_thread_store_count();
}
