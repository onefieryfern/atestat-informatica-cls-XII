#include "graphing.h"
#include "rectangle.h"
#include <algorithm>

/**
 * Transforms a std::vector\<int\> into a std::vector\<Rectangle\> with padding, occupying all of the current rendering
 * target
 * @param renderer
 * @param vector
 * @param colour the colours of the new rectangles
 * @return a std::vector\<Rectangle\> containing the rectangles
 */
std::vector<Rectangle> getRectsFromIntVector(SDL_Renderer *renderer, const std::vector<int>& vector, Rectangle::Colours colour)
{
    // Get current rendering context output size
    int w {}, h {};
    SDL_GetCurrentRenderOutputSize(renderer, &w, &h);
    const float outputWidth { static_cast<float>(w) };
    const float outputHeight { static_cast<float>(h) };

    // Get number of elements we are working with to use later
    const size_t len { vector.size() };

    // Calculate the padding between rectangles
    const float padding = (outputWidth / static_cast<float>(len)) * 0.05f; // in pixels
    const float totalPadding = static_cast<float>(len - 1) * padding;

    // Calculate the width of a rectangle, with padding in mind
    const float rectWidth {(outputWidth - totalPadding) / static_cast<float>(len) };

    // Find the extremes of the elements of the vector
    int greatest = *std::max_element(vector.begin(), vector.end());
    int least = *std::min_element(vector.begin(), vector.end());
    int total_range = (least <= 0 ? std::abs(greatest) + std::abs(least) : std::abs(greatest));

    // Calculate the baseline for positive / negative separation, aka the height of the x-axis
    float baselineY = static_cast<float>(std::abs(greatest)) * (outputHeight / static_cast<float>(total_range));

    std::vector<Rectangle> rects {};
    for (size_t i = 0; i < len; ++i)
    {
        // How much of the screen this element should take as a ratio of the total output height
        float heightPercent = static_cast<float>(std::abs(vector.at(i))) / static_cast<float>(total_range);

        float rectHeight = outputHeight * heightPercent;

        float x = static_cast<float>(i) * (rectWidth + padding);
        float y = (vector.at(i) >= 0 ? baselineY - rectHeight : baselineY);

        Rectangle rect {{x, y, rectWidth, rectHeight}, colour.fill, colour.outline};
        rects.push_back(rect);
    }

    return rects;
}
