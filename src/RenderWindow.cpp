#include "RenderWindow.h"
#include <SDL3/SDL.h>
#include <iostream>

/**
 * @param title the title of the window, in UTF-8 encoding.
 * @param width the width of the window.
 * @param height the height of the window.
 * @param window_flags the flags used to create the window (see SDL_CreateWindow()).
 */
RenderWindow::RenderWindow(const char *title, const int width, const int height, const SDL_WindowFlags window_flags)
{
    SDL_CreateWindowAndRenderer(title, width, height, window_flags, &m_window, &m_renderer);
    if (m_window == nullptr)
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << '\n';
    if (m_renderer == nullptr)
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << '\n';
}

RenderWindow::~RenderWindow()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

SDL_Renderer* RenderWindow::getRenderer() const { return m_renderer; }
SDL_Window* RenderWindow::getWindow() const { return m_window; }

void RenderWindow::blank(const SDL_Color& colour) const
{
    SDL_SetRenderTarget(m_renderer, nullptr);
    SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderClear(m_renderer);
}

void RenderWindow::renderPresent() const { SDL_RenderPresent(m_renderer); }
