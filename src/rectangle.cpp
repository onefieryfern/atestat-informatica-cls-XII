#include "rectangle.h"
#include <SDL3/SDL.h>

void drawRect(
        SDL_Renderer* renderer,
        const SDL_FRect& rect,
        const SDL_Color& fillColour,
        const SDL_Color& outlineColour
                )
{
    SDL_SetRenderDrawColor(renderer, fillColour.r, fillColour.g, fillColour.b, fillColour.a);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, outlineColour.r, outlineColour.g, outlineColour.b, outlineColour.a);
    SDL_RenderRect(renderer, &rect);
}
