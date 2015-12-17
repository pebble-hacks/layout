#include "layout.h"

static void reflow(Layout *this) {
  GSize window_size = this->window_size;
  int size = this->size;

  for(int i = 0; i < size; i++) {  
    GRect frame;
    frame.origin.x = 0;
    frame.size.w = window_size.w;

    switch(this->orientation) {
      case LayoutOrientationVertical: {
        int height = (window_size.h * this->weight_array[i]) / 100;
        frame.origin.y = i * height;
        frame.size.h = height;
      } break;
      case LayoutOrientationHorizontal: {
        int width = (window_size.w * this->weight_array[i]) / 100;
        frame.origin.x = i * width;
        frame.size.w = width;
      } break;
    }

    layer_set_frame(this->layer_array[i], frame);
  }
}

Layout* layout_create(LayoutOrientation orientation, int size) {
  Layout *this = (Layout*)malloc(sizeof(Layout));
  this->orientation = orientation;
  this->size = size;
  this->layer_array = (Layer**)malloc(size * sizeof(Layer*));
  this->weight_array = (int*)malloc(size * sizeof(int));
  return this;
}

void layout_add_layer_with_params(Layout *this, Layer *layer, int slot, int weight) {
  if(slot >= this->size) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Slot is greater than the size of the layout!");
    return;
  }
  if(weight < 0 || weight > 100) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Weight must be 0-100");
    return; 
  }

  int total_weight = 0;
  for(int i = 0; i < this->size; i++) {
    total_weight += this->weight_array[i];
  }
  if(total_weight > 100) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Total weights must be <= 100");
    return;
  }

  this->layer_array[slot] = layer;
  this->weight_array[slot] = weight;

  reflow(this);
}

void layout_destroy(Layout *this) {
  free(this->layer_array);
  free(this->weight_array);
  free(this);
}

void layout_add_to_window(Layout *this, Window *parent) {
  Layer *root_layer = window_get_root_layer(parent);
  this->window_size = layer_get_bounds(root_layer).size;
  
  int size = this->size;
  for(int i = 0; i < size; i++) {
    layer_add_child(root_layer, this->layer_array[i]);
  }

  reflow(this);
}
