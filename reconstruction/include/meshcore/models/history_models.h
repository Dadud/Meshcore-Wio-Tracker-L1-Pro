#ifndef MESHCORE_HISTORY_MODELS_H
#define MESHCORE_HISTORY_MODELS_H

#include <stdbool.h>
#include <stdint.h>

#define MC_MAX_MESSAGE_TEXT 160
#define MC_MAX_SENDER_NAME 48

typedef struct {
  uint32_t timestamp;
  bool outgoing;
  bool acknowledged;
  bool pending;
  char sender[MC_MAX_SENDER_NAME];
  char text[MC_MAX_MESSAGE_TEXT];
} mc_history_message_t;

typedef struct {
  uint32_t last_message_timestamp;
  uint16_t unread_count;
  uint16_t total_count;
  bool muted;
  bool loaded_in_ram;
} mc_history_thread_state_t;

#endif
