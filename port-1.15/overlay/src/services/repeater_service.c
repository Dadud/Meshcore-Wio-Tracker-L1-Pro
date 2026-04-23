#include "meshcore/services/repeater_service.h"

#include <string.h>

static mc_repeater_request_kind_t g_current_kind;
static uint32_t g_current_tag;
static mc_repeater_status_view_t g_status;
static mc_repeater_owner_view_t g_owner;
static mc_repeater_acl_view_t g_acl;
static mc_repeater_neighbours_view_t g_neighbours;

void mc_repeater_service_init(void) {
  g_current_kind = MC_REQ_NONE;
  g_current_tag = 0;
  memset(&g_status, 0, sizeof(g_status));
  memset(&g_owner, 0, sizeof(g_owner));
  memset(&g_acl, 0, sizeof(g_acl));
  memset(&g_neighbours, 0, sizeof(g_neighbours));
}

bool mc_repeater_service_begin_request(mc_repeater_request_kind_t kind, uint32_t tag) {
  g_current_kind = kind;
  g_current_tag = tag;
  return true;
}

bool mc_repeater_service_complete_status(const mc_repeater_status_view_t* view) {
  if (!view) return false;
  g_status = *view;
  g_current_kind = MC_REQ_NONE;
  return true;
}

bool mc_repeater_service_complete_owner(const mc_repeater_owner_view_t* view) {
  if (!view) return false;
  g_owner = *view;
  g_current_kind = MC_REQ_NONE;
  return true;
}

bool mc_repeater_service_complete_acl(const mc_repeater_acl_view_t* view) {
  if (!view) return false;
  g_acl = *view;
  g_current_kind = MC_REQ_NONE;
  return true;
}

bool mc_repeater_service_complete_neighbours(const mc_repeater_neighbours_view_t* view) {
  if (!view) return false;
  g_neighbours = *view;
  g_current_kind = MC_REQ_NONE;
  return true;
}
