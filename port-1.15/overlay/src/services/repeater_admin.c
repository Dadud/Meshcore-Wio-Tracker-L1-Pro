#include "meshcore/services/repeater_admin.h"

#include <string.h>

static mc_repeater_session_state_t g_session;
static mc_repeater_status_view_t g_status;
static mc_repeater_owner_view_t g_owner;
static mc_repeater_acl_view_t g_acl;
static mc_repeater_neighbours_view_t g_neighbours;

static uint16_t rd16(const uint8_t* p) { return (uint16_t)p[0] | ((uint16_t)p[1] << 8); }
static uint32_t rd32(const uint8_t* p) { return (uint32_t)rd16(p) | ((uint32_t)rd16(p + 2) << 16); }

void mc_repeater_admin_init(void) {
  memset(&g_session, 0, sizeof(g_session));
  memset(&g_status, 0, sizeof(g_status));
  memset(&g_owner, 0, sizeof(g_owner));
  memset(&g_acl, 0, sizeof(g_acl));
  memset(&g_neighbours, 0, sizeof(g_neighbours));
}

void mc_repeater_admin_clear(void) {
  mc_repeater_admin_init();
}

void mc_repeater_admin_set_active(const uint8_t pub_key[6], uint8_t channel_idx) {
  if (pub_key) memcpy(g_session.pub_key, pub_key, 6);
  g_session.channel_idx = channel_idx;
}

void mc_repeater_admin_on_login_success(const uint8_t pub_key[6], uint8_t channel_idx) {
  mc_repeater_admin_set_active(pub_key, channel_idx);
  g_session.login_in_progress = false;
  g_session.login_required = false;
  g_session.login_ok = true;
}

void mc_repeater_admin_on_login_fail(const uint8_t pub_key[6], uint8_t channel_idx) {
  mc_repeater_admin_set_active(pub_key, channel_idx);
  g_session.login_in_progress = false;
  g_session.login_required = true;
  g_session.login_ok = false;
}

bool mc_repeater_admin_get_session(mc_repeater_session_state_t* out) {
  if (!out) return false;
  *out = g_session;
  return true;
}

bool mc_repeater_admin_get_status(mc_repeater_status_view_t* out) {
  if (!out || !g_status.valid) return false;
  *out = g_status;
  return true;
}

bool mc_repeater_admin_get_owner(mc_repeater_owner_view_t* out) {
  if (!out || !g_owner.valid) return false;
  *out = g_owner;
  return true;
}

bool mc_repeater_admin_get_acl(mc_repeater_acl_view_t* out) {
  if (!out || !g_acl.valid) return false;
  *out = g_acl;
  return true;
}

bool mc_repeater_admin_get_neighbours(mc_repeater_neighbours_view_t* out) {
  if (!out || !g_neighbours.valid) return false;
  *out = g_neighbours;
  return true;
}

bool mc_repeater_admin_dispatch_status(const uint8_t pub_key[6], uint8_t channel_idx, const uint8_t* payload, int len) {
  if (!payload || len < 24) return false;
  memset(&g_status, 0, sizeof(g_status));
  memcpy(g_status.pub_key, pub_key, 6);
  g_status.channel_idx = channel_idx;
  g_status.battery_mv = rd16(payload + 0);
  g_status.queue_used = rd16(payload + 2);
  g_status.queue_free = rd16(payload + 4);
  g_status.last_rssi = (int16_t)rd16(payload + 6);
  g_status.rx_packets = rd32(payload + 8);
  g_status.tx_packets = rd32(payload + 12);
  g_status.uptime_seconds = rd32(payload + 16);
  g_status.last_snr_tenths = (int16_t)rd16(payload + 20);
  g_status.valid = true;
  mc_repeater_admin_set_active(pub_key, channel_idx);
  g_session.current_request = MC_REQ_NONE;
  g_session.request_pending = false;
  return true;
}
