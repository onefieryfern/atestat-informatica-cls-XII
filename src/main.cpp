#include "config.h"
#include "RenderWindow.h"
#include "utility.h"
#include "VisualSorter/VisualSorter.h"
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
        std::cout << "Possible commands: help, selection, bubble, insertion, comb, cocktail, heap, quick\n";
        return 0;
    }

    // Initialise app configuration
    const config::AppCfg appCfg { config::readFromFile() };

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
    else if (subcommand == "heap"sv)
    {
        windowTitle = "Heapsort"sv;
        sortingMethod = VisualSorter::heap;
    }
    else if (subcommand == "quick"sv)
    {
        windowTitle = "Quicksort"sv;
        sortingMethod = VisualSorter::quick;
    }
    else
    {
        std::cout << "Invalid usage! Do " << argv[0] << " help\n";
        return 0;
    }

    // Instantiate visual sorter
    VisualSorter visualSorter { window, appCfg.barColours };

    // Generate vector to be sorted
    std::vector<int> vector;
    switch (appCfg.vectorGeneratorCfg.type)
    {
    case config::VectorGeneratorCfg::consecutive:
        vector = generateConsecutiveRandomVector(appCfg.vectorGeneratorCfg.min, appCfg.vectorGeneratorCfg.max);
        break;
    case config::VectorGeneratorCfg::random:
        vector = generateRandomVector(appCfg.vectorGeneratorCfg.size, appCfg.vectorGeneratorCfg.min, appCfg.vectorGeneratorCfg.max);
        break;
    }

    // Start sorting
    SDL_SetWindowTitle(window.getWindow(), windowTitle.data());
    visualSorter.startSort(vector, sortingMethod);

    // Do the sorting and draw the results
    while (!visualSorter.hasSortFinished())
    {
        window.blank(appCfg.backgroundColour);
        Rectangle::drawRects(window.getRenderer(), visualSorter.getCurrentStepRects());
        window.renderPresent();

        longDelay(appCfg.delay);
    }
    longDelay(2 * appCfg.delay);

    // Exit gracefully
    window.~RenderWindow();
    SDL_Quit();

    return 0;
}
