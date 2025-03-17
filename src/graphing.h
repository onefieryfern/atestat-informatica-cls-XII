#ifndef ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H
#define ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H

#include "rectangle.h"
#include "render.h"
#include <vector>

struct GraphColours
{
    SDL_Color background = {0x00, 0x00, 0x00, 0xff};
    Rectangle::Colours foreground = {{}, {}};
    Rectangle::Colours highlight = {{}, {}};
};

std::vector<Rectangle> getRectsFromIntVector
(
        SDL_Renderer *renderer,
        const std::vector<int> &vector,
        Rectangle::Colours colour = {{0xff, 0xff, 0xff, 0xff}, {0x00, 0x00, 0x00, 0x00}}
);

void drawRectsFromIntVector
(
        RenderWindow& window,
        const std::vector<int>& vector,
        GraphColours colours,
        const std::vector<size_t>& highlightedRects = {}
);

#endif //ATESTAT_INFORMATICA_CLS_XII_GRAPHING_H
