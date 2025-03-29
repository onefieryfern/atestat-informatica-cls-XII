#include "utility.h"
#include "rectangle.h"
#include <cstdlib>
#include <vector>

/**
 * Sets the colours specified for multiple rects. Meant to simplify code when setting the same colour for a few rects,
 * if you already have a rectangle vector, it is not recommended to use this function, as it copies the array
 * @param rects the rects to colour.
 * @param colour
 */
void setRectsColour(const std::vector<std::reference_wrapper<Rectangle>>& rects, const Rectangle::Colours colour)
{
    for (auto& rectReference : rects)
    {
        rectReference.get().setColours(colour);
    }
}

void longDelay(const int32_t delay)
{
    for (int32_t i = 1; i <= delay; ++i)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                exit(EXIT_SUCCESS);
        }

        SDL_Delay(1);
    }
}
