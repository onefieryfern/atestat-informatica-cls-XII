#ifndef ATESTAT_INFORMATICA_CLS_XII_CONSTANTS_H
#define ATESTAT_INFORMATICA_CLS_XII_CONSTANTS_H

#include <SDL3/SDL.h>

namespace constants
{
    namespace colours
    {
        constexpr SDL_Color white { 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE };
        constexpr SDL_Color black { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };
        constexpr SDL_Color none { 0x00, 0x00, 0x00, SDL_ALPHA_TRANSPARENT };

        constexpr SDL_Color red { 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE };
        constexpr SDL_Color green { 0x00, 0xff, 0x00, SDL_ALPHA_OPAQUE };
        constexpr SDL_Color blue { 0x00, 0x00, 0xff, SDL_ALPHA_OPAQUE };
    }
}

#endif //ATESTAT_INFORMATICA_CLS_XII_CONSTANTS_H
