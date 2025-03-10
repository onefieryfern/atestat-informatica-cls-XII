#include "sort.h"
#include <utility>
#include <vector>

void bubble_sort(std::vector<int>& vector)
{
    const size_t len = vector.size();
    bool sorted = false;

    while (!sorted) {
        sorted = true;

        for (size_t i = 0; i < len - 1; ++i)
        {
            int& current { vector.at(i) };
            int& next { vector.at(i + 1) };

            if (current > next)
            {
                sorted = false;
                std::swap(current, next);
            }
        }
    }
}
