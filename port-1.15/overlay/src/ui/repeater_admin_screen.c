#include "meshcore/ui/repeater_admin_screen.h"
#include "meshcore/services/repeater_admin.h"

#include <stdio.h>

bool mc_repeater_admin_screen_refresh_status(mc_repeater_status_view_t* out) {
  return mc_repeater_admin_get_status(out);
}

bool mc_repeater_admin_screen_format_status(const mc_repeater_status_view_t* in, char* out, int out_len) {
  unsigned long days, hours, mins;
  if (!in || !out || out_len <= 0 || !in->valid) return false;
  days = in->uptime_seconds / 86400UL;
  hours = (in->uptime_seconds % 86400UL) / 3600UL;
  mins = (in->uptime_seconds % 3600UL) / 60UL;
  snprintf(out, (size_t)out_len,
           "Uptime %lud %luh %lum | Q %u/%u | RSSI %d | SNR %.1f | Batt %umV",
           days, hours, mins,
           (unsigned)in->queue_used, (unsigned)(in->queue_used + in->queue_free),
           (int)in->last_rssi, in->last_snr_tenths / 10.0f,
           (unsigned)in->battery_mv);
  return true;
}
