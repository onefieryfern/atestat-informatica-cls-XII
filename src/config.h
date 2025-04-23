#ifndef ATESTAT_INFORMATICA_CLS_XII_CONFIG_H
#define ATESTAT_INFORMATICA_CLS_XII_CONFIG_H

#include "constants.h"
#include "VisualSorter/VisualSorter.h"
#include <SDL3/SDL_pixels.h>
#include <cstddef>
#include <cstdint>
#include <string>

namespace config
{
    using namespace std::literals;

    struct VectorGeneratorCfg
    {
        enum Type { consecutive, random } type {};
        int min {};
        int max {};
        size_t size {}; // only required for random vector generation
    };

    struct AppCfg
    {
        uint32_t delay {};
        SDL_Color backgroundColour {};
        VisualSorter::BarColours barColours {};
        VectorGeneratorCfg vectorGeneratorCfg {};
    };

    constexpr AppCfg defaultAppCfg
    {
        100,
        constants::colours::white,
        {
            { constants::colours::html::slateGrey, constants::colours::none },
            { constants::colours::html::dodgerBlue, constants::colours::none },
            { constants::colours::html::crimson, constants::colours::none },
            { constants::colours::html::mediumSeaGreen, constants::colours::none }
        },
        {
            VectorGeneratorCfg::consecutive,
            0,
            100,
            0
        }
    };

    AppCfg readFromFile(const std::string& filename = "config.conf"s);
}

#endif //ATESTAT_INFORMATICA_CLS_XII_CONFIG_H
