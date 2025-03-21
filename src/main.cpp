#include "graphing.h"
#include "render.h"
#include "sort.h"
#include <SDL3/SDL_main.h>
#include <cstring>
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    // Check arguments
    if (argc < 2)
    {
        std::cout << "Invalid usage! Do " << argv[0] << " help\n";
        return 0;
    }
    else if (strcmp(argv[1], "help") == 0)
    {
        std::cout << "Possible commands: help, selection, bubble, insertion\n";
        return 0;
    }

    // Initialise SDL subsystems
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        std::cerr << "Failed to initialise SDL: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    std::cout << "Hello, World!" << std::endl;

    // Create SDL window and associated renderer
    RenderWindow window {"Hello World", 1920, 1080, SDL_WINDOW_RESIZABLE};
    SDL_SetWindowMinimumSize(window.getWindow(), 640, 360);

    // Test vector and colours
    std::vector<int> v {1, 6, -5, 8, 4, 2, -3, 3, -2, 7};
    constexpr int delay { 300 };

    const SDL_Color backgroundColour { 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE };
    const Rectangle::Colours rectColour { { 0x70, 0x80, 0x90, SDL_ALPHA_OPAQUE }, {} };
    const Rectangle::Colours selectedColour { { 0x1e, 0x90, 0xff, SDL_ALPHA_OPAQUE }, {} };
    const Rectangle::Colours swappedColour { { 0xdc, 0x14, 0x3c, SDL_ALPHA_OPAQUE }, {} };

    // Handle arguments
    if (strcmp(argv[1], "selection") == 0)
    {
        SDL_SetWindowTitle(window.getWindow(), "Selection Sort");
        selection_sort_visual(window, v, delay, backgroundColour, rectColour, selectedColour, swappedColour);
    }
    else if (strcmp(argv[1], "bubble") == 0)
    {
        SDL_SetWindowTitle(window.getWindow(), "Bubble Sort");
        bubble_sort_visual(window, v, delay, backgroundColour, rectColour, selectedColour, swappedColour);
    }
    else if (strcmp(argv[1], "insertion") == 0)
    {
        SDL_SetWindowTitle(window.getWindow(), "Insertion Sort");
        insertion_sort_visual(window, v, delay, backgroundColour, rectColour, selectedColour, swappedColour);
    }
    else
    {
        std::cout << "Invalid usage! Do " << argv[0] << " help\n";
        return 0;
    }

    // Exit gracefully
    window.~RenderWindow();
    SDL_Quit();

    return 0;
}