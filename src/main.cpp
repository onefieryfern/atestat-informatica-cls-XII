#include "sort.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    std::cout << "Hello, World!" << std::endl;

    // Initialise SDL subsystems
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        std::cerr << "Failed to initialise SDL: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    // Create SDL window and associated renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (!SDL_CreateWindowAndRenderer("Hello World", 1920, 1080, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        std::cerr << "Failed to create SDL window and/or renderer: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    SDL_SetWindowMinimumSize(window, 640, 360);

    /*
    std::vector<int> v {4, 2, 6, 3, 1, 5};
    bubble_sort(v);
    for (auto i : v) { std::cout << i << ' '; }
    std::cout << std::endl;
     */

    // Program loop
    bool running = true;
    while (running)
    {
        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        // Start with a "blank canvas"
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the composed frame
        SDL_RenderPresent(renderer);

        SDL_Delay(3);
    }

    // Exit gracefully
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}