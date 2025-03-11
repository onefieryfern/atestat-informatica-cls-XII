#include "rectangle.h"
#include <SDL3/SDL.h>
#include <vector>

Rectangle::Rectangle(SDL_FRect sdlFRect, SDL_Color fillColour, SDL_Color outlineColour)
{
    m_dimensions = sdlFRect;
    m_fillColour = fillColour;
    m_outlineColour = outlineColour;
}

SDL_FRect Rectangle::getDimensions() const { return m_dimensions; }
SDL_Color Rectangle::getFillColour() const { return m_fillColour; }
SDL_Color Rectangle::getOutlineColour() const { return m_outlineColour; }

void Rectangle::setDimensions(SDL_FRect sdlFRect) { m_dimensions = sdlFRect; }
void Rectangle::setFillColour(SDL_Color colour) { m_fillColour = colour; }
void Rectangle::setOutlineColour(SDL_Color colour) { m_outlineColour = colour; }

/**
 * Draw the rectangle on the current rendering target of the specified renderer
 * @param renderer
 */
void Rectangle::draw(SDL_Renderer* renderer) const
{
    if (m_fillColour.a != 0)
    {
        SDL_SetRenderDrawColor(renderer, m_fillColour.r, m_fillColour.g, m_fillColour.b, m_fillColour.a);
        SDL_RenderFillRect(renderer, &m_dimensions);
    }

    if (m_outlineColour.a != 0)
    {
        SDL_SetRenderDrawColor(renderer, m_outlineColour.r, m_outlineColour.g, m_outlineColour.b, m_outlineColour.a);
        SDL_RenderRect(renderer, &m_dimensions);
    }
}

void Rectangle::drawRects(SDL_Renderer *renderer, const std::vector<Rectangle>& rects)
{
    for (const Rectangle& rect : rects)
    {
        rect.draw(renderer);
    }
}
