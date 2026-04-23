#include "meshcore/ui/adapters.h"

static mc_ui_settings_t g_settings;

void mc_settings_overlay_reset_defaults(void) {
  g_settings.home_radio = true;
  g_settings.home_gps = true;
  g_settings.home_time = true;
  g_settings.home_bluetooth = true;
  g_settings.home_sound = true;
  g_settings.input_filter_ms = 0;
  g_settings.advert_sound = true;
  g_settings.gps_enabled = true;
}
