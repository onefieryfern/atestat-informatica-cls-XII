#include "graphing.h"
#include "sort.h"
#include "rectangle.h"
#include "render.h"
#include <cstdlib>
#include <utility>
#include <vector>

void bubble_sort_visual(RenderWindow& window, std::vector<int>& vector, GraphColours graphColours, int delay)
{
    bool swapped = true;
    const size_t len = vector.size();

    while (swapped)
    {
        swapped = false;

        for (size_t i = 0; i < len - 1; ++i)
        {
            // Event handling
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                    exit(0);
            }

            // Draw initial state
            drawRectsFromIntVector(window, vector, graphColours, {i, i + 1});
            SDL_Delay(delay);

            int& current { vector.at(i) };
            int& next { vector.at(i + 1) };

            if (current > next)
            {
                swapped = true;
                std::swap(current, next);

                // Draw new state
                drawRectsFromIntVector(window, vector, graphColours, {i, i + 1});
                SDL_Delay(delay);
            }
        }
    }
}
