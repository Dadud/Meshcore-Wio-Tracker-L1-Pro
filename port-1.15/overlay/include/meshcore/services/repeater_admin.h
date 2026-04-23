#ifndef MESHCORE_REPEATER_ADMIN_H
#define MESHCORE_REPEATER_ADMIN_H

#include <stdbool.h>
#include <stdint.h>
#include "meshcore/models/repeater_models.h"
#include "meshcore/models/repeater_view_models.h"

void mc_repeater_admin_init(void);
void mc_repeater_admin_clear(void);
void mc_repeater_admin_set_active(const uint8_t pub_key[6], uint8_t channel_idx);
void mc_repeater_admin_on_login_success(const uint8_t pub_key[6], uint8_t channel_idx);
void mc_repeater_admin_on_login_fail(const uint8_t pub_key[6], uint8_t channel_idx);
bool mc_repeater_admin_get_session(mc_repeater_session_state_t* out);
bool mc_repeater_admin_get_status(mc_repeater_status_view_t* out);
bool mc_repeater_admin_get_owner(mc_repeater_owner_view_t* out);
bool mc_repeater_admin_get_acl(mc_repeater_acl_view_t* out);
bool mc_repeater_admin_get_neighbours(mc_repeater_neighbours_view_t* out);
bool mc_repeater_admin_dispatch_status(const uint8_t pub_key[6], uint8_t channel_idx, const uint8_t* payload, int len);

#endif
