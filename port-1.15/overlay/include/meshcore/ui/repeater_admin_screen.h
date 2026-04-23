#ifndef MESHCORE_REPEATER_ADMIN_SCREEN_H
#define MESHCORE_REPEATER_ADMIN_SCREEN_H

#include <stdbool.h>
#include "meshcore/models/repeater_view_models.h"

bool mc_repeater_admin_screen_refresh_status(mc_repeater_status_view_t* out);
bool mc_repeater_admin_screen_format_status(const mc_repeater_status_view_t* in, char* out, int out_len);

#endif
