#include "meshcore/ui/app_shell.h"

static mc_screen_id_t g_current = MC_SCREEN_HOME;
static const mc_screen_id_t g_ring[] = {
  MC_SCREEN_HOME,
  MC_SCREEN_MESSAGES,
  MC_SCREEN_CONTACTS,
  MC_SCREEN_CHANNELS,
  MC_SCREEN_ADVERTS,
  MC_SCREEN_RADIO,
  MC_SCREEN_BLUETOOTH,
  MC_SCREEN_SOUND,
  MC_SCREEN_GPS,
  MC_SCREEN_TIME,
  MC_SCREEN_SYSTEM,
  MC_SCREEN_TOOLS,
};

static int find_index(mc_screen_id_t screen) {
  int i;
  for (i = 0; i < (int)(sizeof(g_ring) / sizeof(g_ring[0])); ++i) {
    if (g_ring[i] == screen) return i;
  }
  return 0;
}

void mc_app_shell_init(void) {
  g_current = MC_SCREEN_HOME;
}

mc_screen_id_t mc_app_shell_current(void) {
  return g_current;
}

void mc_app_shell_set_current(mc_screen_id_t screen) {
  g_current = screen;
}

void mc_app_shell_next(void) {
  int i = find_index(g_current);
  i = (i + 1) % (int)(sizeof(g_ring) / sizeof(g_ring[0]));
  g_current = g_ring[i];
}

void mc_app_shell_prev(void) {
  int count = (int)(sizeof(g_ring) / sizeof(g_ring[0]));
  int i = find_index(g_current);
  i = (i + count - 1) % count;
  g_current = g_ring[i];
}
