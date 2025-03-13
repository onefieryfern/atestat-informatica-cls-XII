#ifndef ATESTAT_INFORMATICA_CLS_XII_RENDER_H
#define ATESTAT_INFORMATICA_CLS_XII_RENDER_H

#include <SDL3/SDL.h>
#include <vector>

class RenderWindow
{
private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
public:
    RenderWindow(const char *title, int width, int height, SDL_WindowFlags window_flags);
    ~RenderWindow();

    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();

    void blank(const SDL_Color& colour = {0, 0, 0, 255});
    void renderPresent();
};

#endif //ATESTAT_INFORMATICA_CLS_XII_RENDER_H
