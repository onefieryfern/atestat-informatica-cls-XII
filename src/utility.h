#ifndef ATESTAT_INFORMATICA_CLS_XII_UTILITY_H
#define ATESTAT_INFORMATICA_CLS_XII_UTILITY_H

#include "Rectangle.h"
#include <vector>

void highlightRects
    (
        std::vector<Rectangle>& rects,
        const std::vector<std::vector<size_t>>& highlightIndexes,
        const std::vector<Rectangle::Colour>& highlightColours
    );

void longDelay(int32_t delay);

std::vector<int> generateRandomVector(size_t size, int min, int max);
std::vector<int> generateConsecutiveRandomVector(int from, int to);

#endif //ATESTAT_INFORMATICA_CLS_XII_UTILITY_H
