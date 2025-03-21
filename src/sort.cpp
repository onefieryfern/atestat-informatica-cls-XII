#include "graphing.h"
#include "sort.h"
#include "rectangle.h"
#include "render.h"
#include <cstdlib>
#include <utility>
#include <vector>

void selection_sort_visual
(
    RenderWindow& window,
    std::vector<int>& vector,
    const int delay,
    const SDL_Color& backgroundColour,
    const Rectangle::Colours& rectColour,
    const Rectangle::Colours& selectedColour,
    const Rectangle::Colours& swappedColour
)
{
    const size_t len = vector.size();
    std::vector<Rectangle> rects {};

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
            rects = getRectsFromIntVector(window.getRenderer(), vector, rectColour);
            rects.at(i).setColours(selectedColour);
            rects.at(j).setColours(selectedColour);

            window.blank(backgroundColour);
            Rectangle::drawRects(window.getRenderer(), rects);

            window.renderPresent();
            SDL_Delay(delay);


            int& current { vector.at(i) };
            int& next { vector.at(j) };

            if (current > next)
            {
                std::swap(current, next);

                // Draw new state
                rects = getRectsFromIntVector(window.getRenderer(), vector, rectColour);
                rects.at(i).setColours(swappedColour);
                rects.at(j).setColours(swappedColour);

                window.blank(backgroundColour);
                Rectangle::drawRects(window.getRenderer(), rects);

                window.renderPresent();
                SDL_Delay(delay);
            }
        }
    }

    SDL_Delay(2 * delay);
}

void bubble_sort_visual
(
    RenderWindow& window,
    std::vector<int>& vector,
    const int delay,
    const SDL_Color& backgroundColour,
    const Rectangle::Colours& rectColour,
    const Rectangle::Colours& selectedColour,
    const Rectangle::Colours& swappedColour
)
{
    const size_t len = vector.size();
    std::vector<Rectangle> rects {};

    bool swapped = true;
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
            rects = getRectsFromIntVector(window.getRenderer(), vector, rectColour);
            rects.at(i).setColours(selectedColour);
            rects.at(i + 1).setColours(selectedColour);

            window.blank(backgroundColour);
            Rectangle::drawRects(window.getRenderer(), rects);

            window.renderPresent();
            SDL_Delay(delay);


            int& current { vector.at(i) };
            int& next { vector.at(i + 1) };

            if (current > next)
            {
                swapped = true;
                std::swap(current, next);

                // Draw new state
                rects = getRectsFromIntVector(window.getRenderer(), vector, rectColour);
                rects.at(i).setColours(swappedColour);
                rects.at(i + 1).setColours(swappedColour);

                window.blank(backgroundColour);
                Rectangle::drawRects(window.getRenderer(), rects);

                window.renderPresent();
                SDL_Delay(delay);
            }
        }
    }

    SDL_Delay(2 * delay);
}

void insertion_sort_visual
(
    RenderWindow& window,
    std::vector<int>& vector,
    const int delay,
    const SDL_Color& backgroundColour,
    const Rectangle::Colours& rectColour,
    const Rectangle::Colours& selectedColour,
    const Rectangle::Colours& swappedColour
)
{
    const size_t len = vector.size();
    std::vector<Rectangle> rects {};

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
            rects = getRectsFromIntVector(window.getRenderer(), vector, rectColour);
            rects.at(j).setColours(selectedColour);
            rects.at(j - 1).setColours(selectedColour);

            window.blank(backgroundColour);
            Rectangle::drawRects(window.getRenderer(), rects);

            window.renderPresent();
            SDL_Delay(delay);


            std::swap(vector.at(j), vector.at(j - 1));

            // Draw new state
            rects = getRectsFromIntVector(window.getRenderer(), vector, rectColour);
            rects.at(j).setColours(swappedColour);
            rects.at(j - 1).setColours(swappedColour);

            window.blank(backgroundColour);
            Rectangle::drawRects(window.getRenderer(), rects);

            window.renderPresent();
            SDL_Delay(delay);
        }
    }

    SDL_Delay(2 * delay);
}
