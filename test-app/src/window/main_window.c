#include "main_window.h"

static Window *s_window;
static Layout *s_layout;
static TextLayer *s_top_layer, *s_bottom_layer;

static void timer_handler(void *context) {
  layout_remove_from_window(s_layout);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_layout = layout_create(LayoutOrientationHorizontal, 2);

  s_top_layer = text_layer_create(GRectZero);
  text_layer_set_background_color(s_top_layer, GColorRed);
  layout_add_layer_with_params(s_layout, text_layer_get_layer(s_top_layer), 0, 50);

  s_bottom_layer = text_layer_create(GRectZero);
  text_layer_set_background_color(s_bottom_layer, GColorGreen);
  layout_add_layer_with_params(s_layout, text_layer_get_layer(s_bottom_layer), 1, 50);

  layout_add_to_window(s_layout, window);

  // Test removal
  app_timer_register(5000, timer_handler, NULL);
}

static void window_unload(Window *window) {
  text_layer_destroy(s_top_layer);
  text_layer_destroy(s_bottom_layer);

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
