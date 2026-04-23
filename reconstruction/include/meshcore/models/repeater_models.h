#ifndef MESHCORE_REPEATER_MODELS_H
#define MESHCORE_REPEATER_MODELS_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  MC_REQ_NONE = 0,
  MC_REQ_LOGIN,
  MC_REQ_STATUS,
  MC_REQ_TELEMETRY,
  MC_REQ_OWNER_INFO,
  MC_REQ_ACCESS_LIST,
  MC_REQ_NEIGHBOURS,
} mc_repeater_request_kind_t;

typedef struct {
  bool login_required;
  bool login_in_progress;
  bool login_ok;
  bool request_pending;
  uint8_t telemetry_permissions;
  uint32_t last_request_tag;
  mc_repeater_request_kind_t current_request;
} mc_repeater_session_state_t;

#endif
