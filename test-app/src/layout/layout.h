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
} Layout;

Layout* layout_create(LayoutOrientation orientation, int size);
void layout_destroy(Layout *this);

void layout_add_layer_with_params(Layout *this, Layer *layer, int slot, int weight);