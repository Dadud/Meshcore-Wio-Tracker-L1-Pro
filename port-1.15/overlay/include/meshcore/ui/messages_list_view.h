#ifndef MESHCORE_MESSAGES_LIST_VIEW_H
#define MESHCORE_MESSAGES_LIST_VIEW_H

#include <stdbool.h>
#include "meshcore/models/app_models.h"

typedef struct {
  int selected_index;
  int visible_count;
} mc_messages_list_view_t;

void mc_messages_list_view_init(mc_messages_list_view_t* view);
int mc_messages_list_view_refresh(mc_messages_list_view_t* view, mc_thread_summary_t* out, int max_items);
bool mc_messages_list_view_select_next(mc_messages_list_view_t* view);
bool mc_messages_list_view_select_prev(mc_messages_list_view_t* view);

#endif
