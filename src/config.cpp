#include "config.h"
#include "utility.h"
#include <SDL3/SDL_pixels.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

namespace config
{
    using namespace std::literals;

    SDL_Color parseColourArray(const std::vector<std::string>& tokens)
    {
        SDL_Color colour {};

        if (tokens.size() != 5)
            throw std::invalid_argument("");

        uint64_t red {};
        uint64_t green {};
        uint64_t blue {};
        uint64_t alpha {};

        try
        {
            red = std::stoull(tokens.at(1));
            green = std::stoull(tokens.at(2));
            blue = std::stoull(tokens.at(3));
            alpha = std::stoull(tokens.at(4));
        }
        catch (const std::exception&)
        {
            throw;
        }

        if (red <= std::numeric_limits<uint8_t>::max())
            colour.r = static_cast<uint8_t>(red);
        else
            throw std::out_of_range("");

        if (green <= std::numeric_limits<uint8_t>::max())
            colour.g = static_cast<uint8_t>(green);
        else
            throw std::out_of_range("");

        if (blue <= std::numeric_limits<uint8_t>::max())
            colour.b = static_cast<uint8_t>(blue);
        else
            throw std::out_of_range("");

        if (alpha <= std::numeric_limits<uint8_t>::max())
            colour.a = static_cast<uint8_t>(alpha);
        else
            throw std::out_of_range("");

        return colour;
    }

    void tryParseColourArray(const std::vector<std::string>& tokens, SDL_Color& colour, const std::string_view& keyName)
    {
        try
        {
            colour = parseColourArray(tokens);
        }
        catch (const std::exception&)
        {
            std::cout << "Could not parse " << keyName << ".\n";
        }
    }

    AppCfg readFromFile(const std::string& filename)
    {
        AppCfg config { defaultAppCfg };

        std::ifstream file { filename.c_str() };

        if (!file.is_open())
        {
            std::cout << "Could not open " << filename << ".\n";
            std::cout << "Using default config.\n";
            return config;
        }

        for (std::string line; std::getline(file, line); )
        {
            std::vector tokens { tokeniseString(line, { ' ', '=', '{', '}', ',' }) };

            if (tokens.size() < 2)
                continue;

            const std::string key { tokens.at(0) };
            const std::string value { tokens.at(1) };

            if (key == "delay"s)
            {
                try
                {
                    config.delay = std::stoul(value);

                    if (config.delay == 0)
                    {
                        std::cout << "Delay must be greater than 0.\n";
                        config.delay = defaultAppCfg.delay;
                    }
                }
                catch (const std::exception&)
                {
                    std::cout << "Could not parse delay.\n";
                }
            }
            else if (key == "background_colour"s)
                tryParseColourArray(tokens, config.backgroundColour, "background colour"sv);
            else if (key == "bar_colours_main_fill"s)
                tryParseColourArray(tokens, config.barColours.main.fill, "bar colours main fill"sv);
            else if (key == "bar_colours_main_outline"s)
                tryParseColourArray(tokens, config.barColours.main.outline, "bar colours main outline"sv);
            else if (key == "bar_colours_selected_fill"s)
                tryParseColourArray(tokens, config.barColours.selected.fill, "bar colours selected fill"sv);
            else if (key == "bar_colours_selected_outline"s)
                tryParseColourArray(tokens, config.barColours.selected.outline, "bar colours selected outline"sv);
            else if (key == "bar_colours_acted_on_fill"s)
                tryParseColourArray(tokens, config.barColours.actedOn.fill, "bar colours acted on fill"sv);
            else if (key == "bar_colours_acted_on_outline"s)
                tryParseColourArray(tokens, config.barColours.actedOn.outline, "bar colours acted on outline"sv);
            else if (key == "bar_colours_auxiliary_fill"s)
                tryParseColourArray(tokens, config.barColours.auxiliary.fill, "bar colours auxiliary fill"sv);
            else if (key == "bar_colours_auxiliary_outline"s)
                tryParseColourArray(tokens, config.barColours.auxiliary.outline, "bar colours auxiliary outline"sv);
            else if (key == "vector_generator_type"s)
            {
                if (value == "consecutive"s)
                    config.vectorGeneratorCfg.type = VectorGeneratorCfg::consecutive;
                else if (value == "random"s)
                    config.vectorGeneratorCfg.type = VectorGeneratorCfg::random;
                else
                    std::cout << "Could not parse vector generator type.\n";
            }
            else if (key == "vector_generator_min"s)
            {
                try
                {
                    config.vectorGeneratorCfg.min = std::stoi(value);
                }
                catch (const std::exception&)
                {
                    std::cout << "Could not parse vector generator min.\n";
                }
            }
            else if (key == "vector_generator_max"s)
            {
                try
                {
                    config.vectorGeneratorCfg.max = std::stoi(value);
                }
                catch (const std::exception&)
                {
                    std::cout << "Could not parse vector generator max.\n";
                }
            }
            else if (key == "vector_generator_size"s)
            {
                try
                {
                    config.vectorGeneratorCfg.size = std::stoull(value);
                }
                catch (const std::exception&)
                {
                    std::cout << "Could not parse vector generator size.\n";
                }
            }
        }

        return config;
    }
}
