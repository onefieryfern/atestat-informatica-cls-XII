#include "rectangle.h"
#include <SDL3/SDL.h>

void drawRect(
        SDL_Renderer* renderer,
        const SDL_FRect& rect,
        const RectColourProp& colours
                )
{
    SDL_SetRenderDrawColor(renderer, colours.fillColour.r, colours.fillColour.g, colours.fillColour.b, colours.fillColour.a);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, colours.outlineColour.r, colours.outlineColour.g, colours.outlineColour.b, colours.outlineColour.a);
    SDL_RenderRect(renderer, &rect);
}
