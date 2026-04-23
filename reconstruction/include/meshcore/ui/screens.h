#ifndef MESHCORE_UI_SCREENS_H
#define MESHCORE_UI_SCREENS_H

/*
 * Custom UI layer inferred from firmware-visible strings and workflows.
 * These APIs are reconstruction targets for the app-layer UX sitting on top
 * of upstream MeshCore transport/platform capabilities.
 */

typedef enum {
  MC_SCREEN_HOME = 0,
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
} mc_screen_id_t;

void mc_ui_home_init(void);
void mc_ui_messages_init(void);
void mc_ui_contacts_init(void);
void mc_ui_channels_init(void);
void mc_ui_settings_init(void);

#endif
