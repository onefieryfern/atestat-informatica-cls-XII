#include "sort.h"
#include <utility>
#include <vector>

void bubble_sort(std::vector<int>& vector)
{
    const size_t len = vector.size();
    bool swapped = true;

    while (swapped) {
        swapped = false;

        for (size_t i = 0; i < len - 1; ++i)
        {
            int& current { vector.at(i) };
            int& next { vector.at(i + 1) };

            if (current > next)
            {
                swapped = true;
                std::swap(current, next);
            }
        }
    }
}
