#ifndef MESHCORE_UI_ADAPTERS_H
#define MESHCORE_UI_ADAPTERS_H

#include <stdbool.h>
#include <stdint.h>
#include "meshcore/models/app_models.h"
#include "meshcore/models/history_models.h"
#include "meshcore/models/repeater_models.h"

/*
 * Port-facing adapter interfaces for rebuilding the custom UI layer on top of
 * newer MeshCore core releases.
 */

typedef struct {
  char title[MC_MAX_THREAD_TITLE];
  uint8_t type;
  bool favorite;
  bool is_repeater;
  bool is_room;
  bool is_sensor;
  int32_t gps_lat;
  int32_t gps_lon;
  uint32_t last_seen;
} mc_contact_summary_t;

typedef struct {
  char name[MC_MAX_THREAD_TITLE];
  uint16_t unread_count;
  bool muted;
  bool is_private;
  bool has_shared_key;
} mc_channel_summary_t;

typedef struct {
  bool home_radio;
  bool home_gps;
  bool home_time;
  bool home_bluetooth;
  bool home_sound;
  uint16_t input_filter_ms;
  bool advert_sound;
  bool gps_enabled;
} mc_ui_settings_t;

/* contacts */
int mc_adapt_contacts_count(void);
bool mc_adapt_contacts_get(int index, mc_contact_summary_t* out);
bool mc_adapt_contacts_delete(int index);
bool mc_adapt_contacts_toggle_favorite(int index);

/* channels */
int mc_adapt_channels_count(void);
bool mc_adapt_channels_get(int index, mc_channel_summary_t* out);
bool mc_adapt_channels_set_muted(int index, bool muted);
bool mc_adapt_channels_remove(int index);
bool mc_adapt_channels_join_private_from_text(const char* invite_or_key);
bool mc_adapt_channels_create_private(const char* name, char* out_share_text, int out_len);
bool mc_adapt_channels_detect_private_invite(const char* message_text);

/* threads/history */
int mc_adapt_threads_count(void);
bool mc_adapt_threads_get(int index, mc_thread_summary_t* out);
int mc_adapt_thread_messages_get(int thread_index, int offset, int max_count, mc_history_message_t* out);
bool mc_adapt_thread_clear(int thread_index);
bool mc_adapt_thread_send_text(int thread_index, const char* text);

/* quick text */
int mc_adapt_quick_text_count(void);
bool mc_adapt_quick_text_get(int index, mc_quick_text_t* out);
bool mc_adapt_quick_text_add(const char* text);
bool mc_adapt_quick_text_remove(int index);

/* repeater / telemetry */
bool mc_adapt_repeater_get(int contact_index, mc_repeater_state_t* out);
bool mc_adapt_repeater_session_get(int contact_index, mc_repeater_session_state_t* out);
bool mc_adapt_repeater_login(int contact_index, const char* password);
bool mc_adapt_repeater_request_status(int contact_index);
bool mc_adapt_repeater_request_telemetry(int contact_index, uint8_t mask);
bool mc_adapt_repeater_request_owner_info(int contact_index);
bool mc_adapt_repeater_request_access_list(int contact_index);
bool mc_adapt_repeater_request_neighbours(int contact_index);

/* settings */
bool mc_adapt_settings_load(mc_ui_settings_t* out);
bool mc_adapt_settings_save(const mc_ui_settings_t* in);

#endif
