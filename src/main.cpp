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
        std::cout << "Possible commands: help, bubble, selection\n";
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

    constexpr GraphColours graphColours
            {{0xff, 0xff, 0xff, 0xff},
             {{0x00, 0x00, 0x00, 0xff}, {}},
             {{0xff, 0x00, 0x00, 0xff}, {}}
            };

    // Handle arguments
    if (strcmp(argv[1], "bubble") == 0)
    {
        SDL_SetWindowTitle(window.getWindow(), "Bubble Sort");
        bubble_sort_visual(window, v, graphColours, 200);
    }
    if (strcmp(argv[1], "selection") == 0)
    {
        SDL_SetWindowTitle(window.getWindow(), "Selection Sort");
        selection_sort_visual(window, v, graphColours, 200);
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