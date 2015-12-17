#include "main_window.h"

static Window *s_window;
static Layout *s_layout;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_layout = layout_create(LayoutOrientationVertical, 2);
}

static void window_unload(Window *window) {
  layout_destroy(s_layout);
  window_destroy(window);
}

void main_window_push() {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);
}
