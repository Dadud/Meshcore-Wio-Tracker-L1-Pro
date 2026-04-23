#ifndef MESHCORE_APP_SHELL_H
#define MESHCORE_APP_SHELL_H

#include "meshcore/ui/screens.h"

void mc_app_shell_init(void);
mc_screen_id_t mc_app_shell_current(void);
void mc_app_shell_set_current(mc_screen_id_t screen);
void mc_app_shell_next(void);
void mc_app_shell_prev(void);

#endif
