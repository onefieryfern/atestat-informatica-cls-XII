#ifndef ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H
#define ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H

#include "rectangle.h"
#include <vector>

std::vector<Rectangle> getRectsFromIntVector(SDL_Renderer *renderer, const std::vector<int> &vector, float paddingRatio);

#endif //ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H
