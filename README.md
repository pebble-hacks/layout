# layout

Simple layout library for Pebble SDK. Use instead of settings x, y, width, and
height for `Layer` components manually. Also provides automatic weighting and
spacing of components. This can make settings up simple linear layouts easier.


# How to use

1. Copy the `layout` directory into the `src` directory of your Pebble project.

2. Include `layout.h` where necessary. 

3. Create a `Layout` with the desired orientation and number of elements it will
   eventually contain:

   ```c
   static Layout *s_layout;
   ```

   ```c
   // Create a horizonal layout with two slots
   s_layout = layout_create(LayoutOrientationHorizontal, 2);
   ```

4. After settings up each component, add it to the `Layout` with the appropriate
   slot number it will reside in, and a weight value that will be used for
   spacing:

   ```c
   // Set up a TextLayer
   s_top_layer = text_layer_create(GRectZero);
   text_layer_set_background_color(s_top_layer, GColorRed);

   // Add to the layout in the first slot, with 50% weighting
   layout_add_layer_with_params(s_layout, text_layer_get_layer(s_top_layer), 0, 50);
   ```

5. When all elements have been added, add the `Layout` to the `Window`:

   ```c
   // Display the layout
   layout_add_to_window(s_layout, window);
   ```

6. When the app is exiting, destroy the layout and components separately.

   ```c
   // Destroy components
   text_layer_destroy(s_top_layer);
   text_layer_destroy(s_bottom_layer);

   // Destroy the layout
   layout_destroy(s_layout);
   ```


# Example

See `test-app` for an example use.


# Todo

* Two-dimensional grid layouts
