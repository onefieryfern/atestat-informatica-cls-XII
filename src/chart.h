#ifndef ATESTAT_INFORMATICA_CLS_XII_CHART_H
#define ATESTAT_INFORMATICA_CLS_XII_CHART_H

#include "constants.h"
#include "Rectangle.h"
#include <vector>

namespace chart
{
    std::vector<Rectangle> makeBarChartRects
    (
            SDL_Renderer *renderer,
            const std::vector<int> &vector,
            Rectangle::Colour colour = { constants::colours::white, constants::colours::none }
    );
}

#endif //ATESTAT_INFORMATICA_CLS_XII_CHART_H
