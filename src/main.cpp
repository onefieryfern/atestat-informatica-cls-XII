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
        std::cout << "Possible commands: help, selection, bubble, insertion, comb, cocktail, heapsort, quicksort\n";
        return 0;
    }

    // Default properties
    constexpr int32_t delay { 100 };

    constexpr SDL_Color backgroundColour { constants::colours::white };
    constexpr Rectangle::Colours rectColour
        { constants::colours::html::slateGrey, constants::colours::none };
    constexpr Rectangle::Colours selectedColour
        { constants::colours::html::dodgerBlue, constants::colours::none };
    constexpr Rectangle::Colours swappedColour
        { constants::colours::html::crimson, constants::colours::none };
    constexpr Rectangle::Colours auxiliaryColour
        { constants::colours::html::mediumSeaGreen, constants::colours::none };

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
    else if (subcommand == "comb"sv)
    {
        windowTitle = "Comb Sort"sv;
        sortingMethod = VisualSorter::comb;
    }
    else if (subcommand == "cocktail"sv)
    {
        windowTitle = "Cocktail Shaker Sort"sv;
        sortingMethod = VisualSorter::cocktail;
    }
    else if (subcommand == "heapsort"sv)
    {
        windowTitle = "Heapsort"sv;
        sortingMethod = VisualSorter::heapsort;
    }
    else if (subcommand == "quicksort"sv)
    {
        windowTitle = "Quicksort"sv;
        sortingMethod = VisualSorter::quicksort;
    }
    else
    {
        std::cout << "Invalid usage! Do " << argv[0] << " help\n";
        return 0;
    }

    // Instantiate visual sorter
    VisualSorter visualSorter { window, rectColour, selectedColour, swappedColour, auxiliaryColour };

    // Instantiate test vector
    std::vector<int> vector { generateConsecutiveRandomVector(-10, 10) };

    // Start sorting
    SDL_SetWindowTitle(window.getWindow(), windowTitle.data());
    visualSorter.startSort(vector, sortingMethod);

    // Do the sorting and draw the results
    while (!visualSorter.hasSortFinished())
    {
        window.blank(backgroundColour);
        Rectangle::drawRects(window.getRenderer(), visualSorter.getCurrentStepRects());
        window.renderPresent();

        longDelay(delay);
    }
    longDelay(2 * delay);

    // Exit gracefully
    window.~RenderWindow();
    SDL_Quit();

    return 0;
}
