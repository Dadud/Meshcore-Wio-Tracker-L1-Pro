#ifndef MESHCORE_THREAD_STORE_H
#define MESHCORE_THREAD_STORE_H

#include <stdbool.h>
#include "meshcore/models/app_models.h"
#include "meshcore/models/history_models.h"

#define MC_THREAD_STORE_MAX_THREADS 128
#define MC_THREAD_STORE_MAX_MESSAGES 512

typedef struct {
  mc_thread_summary_t thread;
  mc_history_thread_state_t state;
  int first_message;
  int message_count;
} mc_thread_slot_t;

void mc_thread_store_init(void);
int mc_thread_store_count(void);
bool mc_thread_store_get(int index, mc_thread_summary_t* out);
int mc_thread_store_append_thread(const mc_thread_summary_t* thread);
bool mc_thread_store_append_message(int thread_index, const mc_history_message_t* msg);
int mc_thread_store_get_messages(int thread_index, int offset, int max_count, mc_history_message_t* out);
bool mc_thread_store_mark_read(int thread_index);
bool mc_thread_store_clear(int thread_index);

#endif
