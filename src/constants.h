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

        namespace html
        {
            constexpr SDL_Color slateGrey { 0x70, 0x80, 0x90, SDL_ALPHA_OPAQUE };
            constexpr SDL_Color dodgerBlue { 0x1e, 0x90, 0xff, SDL_ALPHA_OPAQUE };
            constexpr SDL_Color crimson { 0xdc, 0x14, 0x3c, SDL_ALPHA_OPAQUE };
            constexpr SDL_Color mediumSeaGreen { 0x3c, 0xb3, 0x71, SDL_ALPHA_OPAQUE };
        }
    }
}

#endif //ATESTAT_INFORMATICA_CLS_XII_CONSTANTS_H
