#include "graphing.h"
#include "sort.h"
#include "rectangle.h"
#include "render.h"
#include <cstdlib>
#include <utility>
#include <vector>

void selection_sort_visual(RenderWindow& window, std::vector<int>& vector, GraphColours graphColours, int delay)
{
    const size_t len = vector.size();

    for (size_t i = 0; i < len; ++i)
    {
        for (size_t j = i + 1; j < len; ++j)
        {
            // Event handling
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                    exit(0);
            }

            // Draw initial state
            drawRectsFromIntVector(window, vector, graphColours, {i, j});
            SDL_Delay(delay);

            int& current { vector.at(i) };
            int& next { vector.at(j) };

            if (current > next)
            {
                std::swap(current, next);

                // Draw new state
                drawRectsFromIntVector(window, vector, graphColours, {i, j});
                SDL_Delay(delay);
            }
        }
    }
}

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

void insertion_sort_visual(RenderWindow& window, std::vector<int>& vector, GraphColours graphColours, int delay)
{
    const size_t len = vector.size();

    for (size_t i = 1; i < len; ++i)
    {
        for (size_t j = i; j > 0 && vector.at(j - 1) > vector.at(j); --j)
        {
            // Event handling
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                    exit(0);
            }

            // Draw initial state
            drawRectsFromIntVector(window, vector, graphColours, {j, j - 1});
            SDL_Delay(delay);

            std::swap(vector.at(j), vector.at(j - 1));

            // Draw new state
            drawRectsFromIntVector(window, vector, graphColours, {j, j - 1});
            SDL_Delay(delay);
        }
    }
}
