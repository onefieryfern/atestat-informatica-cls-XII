#include "visual.h"
#include "rectangle.h"
#include <SDL3/SDL.h>
#include <vector>

void drawIntVector(SDL_Renderer* renderer, const std::vector<int>& vector, float paddingPercent, const RectColourProp& colours)
{
    int sw {}, sh {};
    SDL_GetCurrentRenderOutputSize(renderer, &sw, &sh);
    const float screenWidth { static_cast<float>(sw) }, screenHeight { static_cast<float>(sh) };

    const size_t len { vector.size() };
    const float padding = paddingPercent * screenWidth; // in pixels
    const float rectWidth { (screenWidth - static_cast<float>(len - 1) * padding) / static_cast<float>(len) };

    for (size_t i = 0; i < len; ++i)
    {
        float heightPercent = static_cast<float>(vector.at(i)) / static_cast<float>(len);
        SDL_FRect rect {static_cast<float>(i) * (rectWidth + padding), (1 - heightPercent) * screenHeight, rectWidth, heightPercent * screenHeight};
        drawRect(renderer, rect, colours);
    }
}
