#ifndef ATESTAT_INFORMATICA_CLS_XII_RENDER_H
#define ATESTAT_INFORMATICA_CLS_XII_RENDER_H

#include "constants.h"
#include <SDL3/SDL.h>

class RenderWindow
{
private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
public:
    RenderWindow(const char *title, int width, int height, SDL_WindowFlags window_flags);
    ~RenderWindow();

    [[nodiscard]] SDL_Renderer* getRenderer() const;
    [[nodiscard]] SDL_Window* getWindow() const;

    void blank(const SDL_Color& colour = constants::colours::black) const;
    void renderPresent() const;
};

#endif //ATESTAT_INFORMATICA_CLS_XII_RENDER_H
