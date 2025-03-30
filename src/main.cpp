#include "render.h"
#include "utility.h"
#include "VisualSorter.h"
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string_view>
#include <vector>

int main(int argc, char** argv)
{
    using namespace std::literals;

    // Check arguments
    if (argc < 2)
    {
        std::cout << "Invalid usage! Do " << argv[0] << " help\n";
        return 0;
    }

    const std::string_view subcommand { argv[1] };
    if (subcommand == "help"sv)
    {
        std::cout << "Possible commands: help, selection, bubble, insertion\n";
        return 0;
    }

    // Default properties
    constexpr int32_t delay { 300 };

    constexpr SDL_Color backgroundColour { constants::colours::white };
    constexpr Rectangle::Colours rectColour
        { { 0x70, 0x80, 0x90, SDL_ALPHA_OPAQUE }, constants::colours::none };
    constexpr Rectangle::Colours selectedColour
        { { 0x1e, 0x90, 0xff, SDL_ALPHA_OPAQUE }, constants::colours::none };
    constexpr Rectangle::Colours swappedColour
        { { 0xdc, 0x14, 0x3c, SDL_ALPHA_OPAQUE }, constants::colours::none };

    // Initialise SDL subsystems
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        std::cerr << "Failed to initialise SDL: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    // Create SDL window and associated renderer
    RenderWindow window {"Hello World", 1920, 1080, SDL_WINDOW_RESIZABLE};
    SDL_SetWindowMinimumSize(window.getWindow(), 640, 360);

    // Display message after successful startup
    std::cout << "Hello, World!" << std::endl;

    // Handle arguments
    std::string_view windowTitle {};
    VisualSorter::SortingMethod sortingMethod {};

    if (subcommand == "selection"sv)
    {
        windowTitle = "Selection Sort"sv;
        sortingMethod = VisualSorter::selection;
    }
    else if (subcommand == "bubble"sv)
    {
        windowTitle = "Bubble Sort"sv;
        sortingMethod = VisualSorter::bubble;
    }
    else if (subcommand == "insertion"sv)
    {
        windowTitle = "Insertion Sort"sv;
        sortingMethod = VisualSorter::insertion;
    }
    else
    {
        std::cout << "Invalid usage! Do " << argv[0] << " help\n";
        return 0;
    }

    // Instantiate visual sorter
    VisualSorter visualSorter { window, { backgroundColour, rectColour, selectedColour, swappedColour } };

    // Instantiate test vector
    std::vector<int> vector { 1, 6, -5, 8, 4, 2, -3, 3, -2, 7 };

    // Start sorting
    SDL_SetWindowTitle(window.getWindow(), windowTitle.data());
    visualSorter.startSort(vector, sortingMethod);

    // Do the sorting and draw the results
    while (!visualSorter.hasSortFinished())
    {
        window.blank(backgroundColour);
        Rectangle::drawRects(window.getRenderer(), visualSorter.getNextStepRects());
        window.renderPresent();

        longDelay(delay);
    }
    longDelay(2 * delay);

    // Exit gracefully
    window.~RenderWindow();
    SDL_Quit();

    return 0;
}
