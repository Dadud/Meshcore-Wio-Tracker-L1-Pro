#ifndef MESHCORE_REPEATER_SERVICE_H
#define MESHCORE_REPEATER_SERVICE_H

#include <stdbool.h>
#include <stdint.h>
#include "meshcore/models/repeater_models.h"
#include "meshcore/models/repeater_view_models.h"

void mc_repeater_service_init(void);
bool mc_repeater_service_begin_request(mc_repeater_request_kind_t kind, uint32_t tag);
bool mc_repeater_service_complete_status(const mc_repeater_status_view_t* view);
bool mc_repeater_service_complete_owner(const mc_repeater_owner_view_t* view);
bool mc_repeater_service_complete_acl(const mc_repeater_acl_view_t* view);
bool mc_repeater_service_complete_neighbours(const mc_repeater_neighbours_view_t* view);

#endif
