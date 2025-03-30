#ifndef ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H
#define ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H

#include "constants.h"
#include "rectangle.h"
#include <vector>

struct GraphColours
{
    SDL_Color background { constants::colours::white };
    Rectangle::Colours foreground = { constants::colours::none, constants::colours::none };
    Rectangle::Colours highlight = { constants::colours::none, constants::colours::none };
};

std::vector<Rectangle> getRectsFromIntVector
(
        SDL_Renderer *renderer,
        const std::vector<int> &vector,
        Rectangle::Colours colour = { constants::colours::white, constants::colours::none }
);

#endif //ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H
