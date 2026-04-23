#include "meshcore/ui/adapters.h"
#include "meshcore/reconstruction.h"

/*
 * Adapter stubs. These should become the compatibility layer between the
 * reconstructed custom UI and the underlying MeshCore version being targeted.
 */

int mc_adapt_contacts_count(void) { return 0; }
bool mc_adapt_contacts_get(int index, mc_contact_summary_t* out) { (void)index; (void)out; return false; }
bool mc_adapt_contacts_delete(int index) { (void)index; return false; }
bool mc_adapt_contacts_toggle_favorite(int index) { (void)index; return false; }

int mc_adapt_channels_count(void) { return 0; }
bool mc_adapt_channels_get(int index, mc_channel_summary_t* out) { (void)index; (void)out; return false; }
bool mc_adapt_channels_set_muted(int index, bool muted) { (void)index; (void)muted; return false; }
bool mc_adapt_channels_remove(int index) { (void)index; return false; }
bool mc_adapt_channels_join_private_from_text(const char* invite_or_key) { (void)invite_or_key; return false; }
bool mc_adapt_channels_create_private(const char* name, char* out_share_text, int out_len) { (void)name; (void)out_share_text; (void)out_len; return false; }
bool mc_adapt_channels_detect_private_invite(const char* message_text) { (void)message_text; return false; }

int mc_adapt_threads_count(void) { return 0; }
bool mc_adapt_threads_get(int index, mc_thread_summary_t* out) { (void)index; (void)out; return false; }
int mc_adapt_thread_messages_get(int thread_index, int offset, int max_count, mc_history_message_t* out) { (void)thread_index; (void)offset; (void)max_count; (void)out; return 0; }
bool mc_adapt_thread_clear(int thread_index) { (void)thread_index; return false; }
bool mc_adapt_thread_send_text(int thread_index, const char* text) { (void)thread_index; (void)text; return false; }

int mc_adapt_quick_text_count(void) { return 0; }
bool mc_adapt_quick_text_get(int index, mc_quick_text_t* out) { (void)index; (void)out; return false; }
bool mc_adapt_quick_text_add(const char* text) { (void)text; return false; }
bool mc_adapt_quick_text_remove(int index) { (void)index; return false; }

bool mc_adapt_repeater_get(int contact_index, mc_repeater_state_t* out) { (void)contact_index; (void)out; return false; }
bool mc_adapt_repeater_session_get(int contact_index, mc_repeater_session_state_t* out) { (void)contact_index; (void)out; return false; }
bool mc_adapt_repeater_login(int contact_index, const char* password) { (void)contact_index; (void)password; return false; }
bool mc_adapt_repeater_request_status(int contact_index) { (void)contact_index; return false; }
bool mc_adapt_repeater_request_telemetry(int contact_index, uint8_t mask) { (void)contact_index; (void)mask; return false; }
bool mc_adapt_repeater_request_owner_info(int contact_index) { (void)contact_index; return false; }
bool mc_adapt_repeater_request_access_list(int contact_index) { (void)contact_index; return false; }
bool mc_adapt_repeater_request_neighbours(int contact_index) { (void)contact_index; return false; }

bool mc_adapt_settings_load(mc_ui_settings_t* out) { (void)out; return false; }
bool mc_adapt_settings_save(const mc_ui_settings_t* in) { (void)in; return false; }
