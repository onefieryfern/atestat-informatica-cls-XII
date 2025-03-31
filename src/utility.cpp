#include "utility.h"
#include "rectangle.h"
#include <algorithm>
#include <cstdlib>
#include <random>
#include <stdexcept>
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

/**
 * Generates a random std::vector<int> with random ints between min and max (inclusive) where the ints do not repeat
 *
 * Zero (0) is also excluded
 * @param size the size of the returned vector
 * @param min
 * @param max
 * @return a filled std::vector<int>
 */
std::vector<int> generateRandomVector(const size_t size, const int min, const int max)
{
    if (size > std::abs(min) + std::abs(max))
        throw std::invalid_argument { "Cannot build a vector of this size without repeating values." };

    // Seed our Mersenne Twister
    std::mt19937 mt{ std::random_device{}() };

    // Create a reusable random number generator that generates uniform numbers between min and max
    std::uniform_int_distribution<> die{ min, max };

    std::vector<int> vector (size);
    for (size_t i = 0; i < size; )
    {
        const int randomVal = die(mt);
        if (randomVal != 0 && std::ranges::find(vector, randomVal) == vector.end())
        {
            vector.at(i) = randomVal;
            ++i;
        }
    }

    return vector;
}
