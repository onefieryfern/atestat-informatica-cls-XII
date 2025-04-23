#include "utility.h"
#include "Rectangle.h"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

/**
 * Applies layered highlighting to rectangles
 *
 * This function assumes the indexes provided are valid, but bounds checking is also done by std::vector::at
 *
 * @param rects the rects to highlight
 * @param highlightIndexes a vector of vectors, each holding the indexes of the rectangles to be coloured with the
 * corresponding colour from highlightColours, ordered from the lowest to the highest layer
 * @param highlightColours a vector of the colours to highlight the rectangles with, if its size does not match
 * highlightIndexes' size, the first colour will be used for all highlighting done
 */
void highlightRects
    (
        std::vector<Rectangle>& rects,
        const std::vector<std::vector<size_t>>& highlightIndexes,
        const std::vector<Rectangle::Colour>& highlightColours
    )
{
    const bool firstColourOnly { highlightColours.size() < highlightIndexes.size() };
    if (firstColourOnly)
        std::cerr << "Warning: highlightRects was provided with multiple vectors of indexes and not enough colours\n";

    const size_t len { highlightIndexes.size() };
    for (size_t i = 0; i < len; ++i)
    {
        auto& currentIndexes { highlightIndexes.at(i) };
        const Rectangle::Colour currentColour { firstColourOnly ? highlightColours.at(0) : highlightColours.at(i) };

        for (const auto index : currentIndexes)
        {
            rects.at(index).setColour(currentColour);
        }
    }
}

void longDelay(const uint32_t delay)
{
    for (uint32_t i = 1; i <= delay; ++i)
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
std::vector<int> generateRandomVector(const size_t size, int min, int max)
{
    if (size > std::abs(min) + std::abs(max))
        throw std::invalid_argument { "Cannot build a vector of this size without repeating values." };

    if (min > max)
    {
        std::swap(min, max);
        std::cerr << "Warning: generateRandomVector was called with min > max\n";
    }

    // Seed our Mersenne Twister
    std::mt19937 mt{ std::random_device{}() };

    // Create a reusable random number generator that generates uniform numbers between min and max
    std::uniform_int_distribution die{ min, max };

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

/**
 * Generates a random std::vector<int> with all consecutive ints between min and max (inclusive) where the ints do not
 * repeat
 *
 * Zero (0) is excluded
 * @param from
 * @param to
 * @return a filled std::vector<int>
 */
std::vector<int> generateConsecutiveRandomVector(int from, int to)
{
    if (from > to)
    {
        std::swap(from, to);
        std::cerr << "Warning: generateConsecutiveRandomVector was called with from > to\n";
    }

    // Seed our Mersenne Twister
    std::mt19937 mt{ std::random_device{}() };

    // Create a reusable random number generator that generates uniform numbers between from and to
    std::uniform_int_distribution<> die{ from, to };

    size_t len { static_cast<size_t>(to - from + 1) };
    if (from * to <= 0)
        len--;

    std::vector<int> vector (len);
    for (size_t i = 0; i < len; )
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

/**
 * Finds the first position of any character in string
 *
 * @param string the string to be searched
 * @param characters the characters to search for
 * @return the found position or std::string::npos if the string does not contain any of the characters provided
 */
size_t findFirstCharPosInString(const std::string& string, const std::vector<char>& characters)
{
    size_t foundPos { std::string::npos };

    for (const auto character : characters)
    {
        foundPos = std::min(foundPos, string.find_first_of(character));
    }

    return foundPos;
}

/**
 * Tokenises a string according to the provided delimiters
 *
 * @param string the string to be tokenised
 * @param delimiters the characters which separate the tokens
 * @return a std::vector<std::string> with the found tokens
 */
std::vector<std::string> tokeniseString(std::string string, const std::vector<char>& delimiters)
{
    std::vector<std::string> tokens {};

    while (true)
    {
        size_t firstDelimPos { findFirstCharPosInString(string, delimiters) };

        // If a delimiter is found at the start
        for ( ; !string.empty() && firstDelimPos == 0; firstDelimPos = findFirstCharPosInString(string, delimiters))
        {
            string = string.substr(1, std::string::npos);
        }

        // If no more delimiters are found
        if (firstDelimPos == std::string::npos)
        {
            if (!string.empty())
                tokens.push_back(string);

            break;
        }

        // Save found token
        tokens.push_back(string.substr(0, firstDelimPos));
        if (firstDelimPos + 1 < string.size())
            string = string.substr(firstDelimPos + 1, std::string::npos);
        else
            break;
    }

    return tokens;
}
