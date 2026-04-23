#include "meshcore/ui/messages_list_view.h"
#include "meshcore/services/thread_store.h"

void mc_messages_list_view_init(mc_messages_list_view_t* view) {
  if (!view) return;
  view->selected_index = 0;
  view->visible_count = 0;
}

int mc_messages_list_view_refresh(mc_messages_list_view_t* view, mc_thread_summary_t* out, int max_items) {
  int i, count;
  if (!view || !out || max_items <= 0) return 0;
  count = mc_thread_store_count();
  if (count > max_items) count = max_items;
  for (i = 0; i < count; ++i) {
    if (!mc_thread_store_get(i, &out[i])) break;
  }
  view->visible_count = i;
  if (view->selected_index >= view->visible_count && view->visible_count > 0) {
    view->selected_index = view->visible_count - 1;
  }
  return i;
}

bool mc_messages_list_view_select_next(mc_messages_list_view_t* view) {
  if (!view || view->visible_count <= 0) return false;
  if (view->selected_index + 1 < view->visible_count) {
    view->selected_index++;
    return true;
  }
  return false;
}

bool mc_messages_list_view_select_prev(mc_messages_list_view_t* view) {
  if (!view || view->visible_count <= 0) return false;
  if (view->selected_index > 0) {
    view->selected_index--;
    return true;
  }
  return false;
}
