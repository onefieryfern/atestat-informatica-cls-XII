#ifndef ATESTAT_INFORMATICA_CLS_XII_UTILITY_H
#define ATESTAT_INFORMATICA_CLS_XII_UTILITY_H

#include "rectangle.h"
#include <vector>

void setRectsColour(const std::vector<std::reference_wrapper<Rectangle>>& rects, Rectangle::Colours colour);
void longDelay(int32_t delay);

std::vector<int> generateRandomVector(size_t size, int min, int max);

#endif //ATESTAT_INFORMATICA_CLS_XII_UTILITY_H
