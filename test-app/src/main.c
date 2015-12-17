#include <pebble.h>

#include "window/main_window.h"

void init() {
  main_window_push();
}

static void deinit() { }

int main() {
  init();
  app_event_loop();
  deinit();
}
