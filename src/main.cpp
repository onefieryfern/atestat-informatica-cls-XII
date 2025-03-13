#include "graphing.h"
#include "rectangle.h"
#include "render.h"
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
    RenderWindow window {"Hello World", 1920, 1080, SDL_WINDOW_RESIZABLE};
    SDL_SetWindowMinimumSize(window.getWindow(), 640, 360);

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
        window.blank({0xff, 0xff, 0xff, 0xff});

        // Compose the frame
        std::vector<int> v {1, 6, -5, 8, 4, 2, -3};

        auto rects = getRectsFromIntVector(window.getRenderer(), v, 0.01f);
        for (Rectangle& rect : rects)
        {
            rect.setFillColour({0xff, 0x36, 0x24, 0xff});
            rect.setOutlineColour({0, 0, 0, 0});
        }
        Rectangle::drawRects(window.getRenderer(), rects);

        // Render the composed frame
        window.renderPresent();

        SDL_Delay(3);
    }

    // Exit gracefully
    window.~RenderWindow();
    SDL_Quit();

    return 0;
}