#ifndef ATESTAT_INFORMATICA_CLS_XII_SORT_VISUAL_H
#define ATESTAT_INFORMATICA_CLS_XII_SORT_VISUAL_H

#include <SDL3/SDL.h>
#include <vector>

#include "rectangle.h"

void drawIntVector(SDL_Renderer* renderer, const std::vector<int>& vector, float paddingPercent, const RectColourProp& colours);

#endif //ATESTAT_INFORMATICA_CLS_XII_SORT_VISUAL_H
