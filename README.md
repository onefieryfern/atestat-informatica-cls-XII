# Atestat informatică clasa a XII-a

## Config

The app is able to read config values from a `config.conf` file found in the same directory as itself. The config file
is not automatically generated if it is not found.

### Known configuration keys

Note: colour array - an array of 4 _unsigned 8-bit integers_ representing RED, GREEN, BLUE and ALPHA colour values

- `delay` (unsigned 32-bit integer)
- `background_colour` (colour array)
- `bar_colours_main_fill` (colour array)
- `bar_colours_main_outline` (colour array)
- `bar_colours_selected_fill` (colour array)
- `bar_colours_selected_outline` (colour array)
- `bar_colours_acted_on_fill` (colour array)
- `bar_colours_acted_on_outline` (colour array)
- `bar_colours_auxiliary_fill` (colour array)
- `bar_colours_auxiliary_outline` (colour array)
- `vector_generator_type` (string containing either of the following: `consecutive`, `random`)
- `vector_generator_min` (implementation-defined `int`)
- `vector_generator_max` (implementation-defined `int`)
- `vector_generator_size` (integer of type `size_t`, required only for vector generator of type `random`)

### Example (default configuration values)

```
delay = 100
background_colour = { 255, 255, 255, 255 }
bar_colours_main_fill = { 112, 128, 144, 255 }
bar_colours_main_outline = { 0, 0, 0, 0 }
bar_colours_selected_fill = { 30, 144, 255, 255 }
bar_colours_selected_outline = { 0, 0, 0, 0 }
bar_colours_acted_on_fill = { 220, 20, 60, 255 }
bar_colours_acted_on_outline = { 0, 0, 0, 0 }
bar_colours_auxiliary_fill = { 60, 179, 113, 255 }
bar_colours_auxiliary_outline = { 0, 0, 0, 0 }
vector_generator_type = consecutive
vector_generator_min = 0
vector_generator_max = 100
vector_generator_size = 0
```

## Attribution

- for Quicksort
  - [GeeksforGeeks](https://www.geeksforgeeks.org/iterative-quick-sort/)
  - [Wikipedia](https://en.wikipedia.org/wiki/Quicksort)
- for Cycle sort
  - [GeeksforGeeks](https://www.geeksforgeeks.org/cycle-sort/)
  - [Wikipedia](https://en.wikipedia.org/wiki/Cycle_sort)
