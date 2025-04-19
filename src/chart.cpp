#include "chart.h"
#include "rectangle.h"
#include <algorithm>
#include <vector>

namespace chart
{
    /**
     * Transforms a std::vector\<int\> into a std::vector\<Rectangle\> with padding, occupying the whole of the current
     * rendering target
     * @param renderer
     * @param vector
     * @param colour the colour of the new rectangles
     * @return a std::vector\<Rectangle\> containing the rectangles
     */
    std::vector<Rectangle> makeBarChartRects(SDL_Renderer *renderer, const std::vector<int>& vector, const Rectangle::Colours colour)
    {
        // Get current rendering context output size
        int w {}, h {};
        SDL_GetCurrentRenderOutputSize(renderer, &w, &h);
        const float outputWidth { static_cast<float>(w) };
        const float outputHeight { static_cast<float>(h) };

        // Get number of elements we are working with to use later
        const size_t len { vector.size() };

        // Calculate the padding between rectangles
        const float padding { std::max(1.0f, (outputWidth / static_cast<float>(len)) * 0.05f) }; // in pixels
        const float totalPadding { static_cast<float>(len - 1) * padding };

        // Calculate the width of a rectangle, with padding in mind
        const float rectWidth { (outputWidth - totalPadding) / static_cast<float>(len) };

        // Find the extremes of the elements of the vector
        const int greatest { *std::ranges::max_element(vector) };
        const int least { *std::ranges::min_element(vector) };
        const int total_range
            { (least * greatest <= 0 ? std::abs(greatest) + std::abs(least) : std::max(std::abs(least), std::abs(greatest))) };

        // Calculate the baseline for positive / negative separation, aka the height of the x-axis
        const float baselineY
            { static_cast<float>(std::max(greatest, 0)) * (outputHeight / static_cast<float>(total_range)) };

        std::vector<Rectangle> rects {};
        for (size_t i = 0; i < len; ++i)
        {
            // How much of the screen this element should take as a ratio of the total output height
            const float heightPercent { static_cast<float>(std::abs(vector.at(i))) / static_cast<float>(total_range) };

            const float rectHeight { outputHeight * heightPercent };

            const float x { static_cast<float>(i) * (rectWidth + padding) };
            const float y { (vector.at(i) >= 0 ? baselineY - rectHeight : baselineY) };

            Rectangle rect { {x, y, rectWidth, rectHeight}, colour };
            rects.push_back(rect);
        }

        return rects;
    }
}
