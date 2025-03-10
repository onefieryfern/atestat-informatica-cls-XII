#ifndef ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H
#define ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H

#include <SDL3/SDL.h>

struct RectColourProp
{
    SDL_Color fillColour {0, 0, 0, 0};
    SDL_Color outlineColour {0, 0, 0, 0};
};

/**
 * Draw a (filled) rectangle with the colour(s) specified on the current rendering target
 */
void drawRect(
        SDL_Renderer* renderer,
        const SDL_FRect& rect,
        const RectColourProp& = {{0, 0, 0, 0}, {0, 0, 0, 0}}
);

#endif //ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H
