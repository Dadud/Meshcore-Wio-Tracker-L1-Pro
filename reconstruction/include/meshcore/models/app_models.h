#ifndef MESHCORE_APP_MODELS_H
#define MESHCORE_APP_MODELS_H

#include <stdint.h>
#include <stdbool.h>

#define MC_MAX_QUICK_TEXTS 32
#define MC_MAX_QUICK_TEXT_LEN 96
#define MC_MAX_THREADS 128
#define MC_MAX_THREAD_TITLE 48
#define MC_MAX_REPEATER_ACTIONS 16

typedef enum {
  MC_THREAD_DIRECT = 0,
  MC_THREAD_CHANNEL,
} mc_thread_kind_t;

typedef struct {
  char text[MC_MAX_QUICK_TEXT_LEN];
  bool in_use;
} mc_quick_text_t;

typedef struct {
  mc_thread_kind_t kind;
  char title[MC_MAX_THREAD_TITLE];
  uint16_t unread_count;
  uint16_t total_count;
  bool muted;
  bool is_private;
} mc_thread_summary_t;

typedef enum {
  MC_REPEATER_ACTION_LOGIN = 0,
  MC_REPEATER_ACTION_STATUS,
  MC_REPEATER_ACTION_TELEMETRY,
  MC_REPEATER_ACTION_OWNER_INFO,
  MC_REPEATER_ACTION_ACCESS_LIST,
  MC_REPEATER_ACTION_NEIGHBOURS,
} mc_repeater_action_t;

typedef struct {
  char display_name[MC_MAX_THREAD_TITLE];
  bool login_required;
  bool login_in_progress;
  bool login_ok;
  uint8_t telemetry_permissions;
} mc_repeater_state_t;

#endif
