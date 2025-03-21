#ifndef ATESTAT_INFORMATICA_CLS_XII_SORT_H
#define ATESTAT_INFORMATICA_CLS_XII_SORT_H

#include "render.h"
#include <vector>

void selection_sort_visual
(
    RenderWindow& window,
    std::vector<int>& vector,
    int delay,
    const SDL_Color& backgroundColour,
    const Rectangle::Colours& rectColour,
    const Rectangle::Colours& selectedColour,
    const Rectangle::Colours& swappedColour
);

void bubble_sort_visual
(
    RenderWindow& window,
    std::vector<int>& vector,
    int delay,
    const SDL_Color& backgroundColour,
    const Rectangle::Colours& rectColour,
    const Rectangle::Colours& selectedColour,
    const Rectangle::Colours& swappedColour
);

void insertion_sort_visual
(
    RenderWindow& window,
    std::vector<int>& vector,
    int delay,
    const SDL_Color& backgroundColour,
    const Rectangle::Colours& rectColour,
    const Rectangle::Colours& selectedColour,
    const Rectangle::Colours& swappedColour
);

#endif //ATESTAT_INFORMATICA_CLS_XII_SORT_H
