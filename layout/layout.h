#pragma once

#include <pebble.h>

typedef enum {
  LayoutOrientationVertical = 0,
  LayoutOrientationHorizontal
} LayoutOrientation;

typedef struct {
  LayoutOrientation orientation;
  int size;
  Layer** layer_array;
  int *weight_array;
  GSize window_size;
} Layout;

Layout* layout_create(LayoutOrientation orientation, int size);

void layout_destroy(Layout *this);

void layout_add_layer_with_params(Layout *this, Layer *layer, int slot, int weight);

void layout_add_to_window(Layout *this, Window *parent);

Layer* layout_get_layer(Layout *this, int slot);

int layout_get_layer_weight(Layout *this, int slot);

void layout_remove_from_window(Layout *this);

void layout_remove_layer(Layout *this, int slot);
