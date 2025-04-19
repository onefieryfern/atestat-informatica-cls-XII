#include "Rectangle.h"
#include <SDL3/SDL.h>
#include <vector>

Rectangle::Rectangle(const SDL_FRect rect, const Colour colour)
{
    m_dimensions = rect;
    m_colour = colour;
}

SDL_FRect Rectangle::getDimensions() const { return m_dimensions; }
Rectangle::Colour Rectangle::getColour() const { return m_colour; }

void Rectangle::setDimensions(const SDL_FRect sdlFRect) { m_dimensions = sdlFRect; }
void Rectangle::setColour(const Colour colour) { m_colour = colour; }

/**
 * Draw the rectangle on the current rendering target of the specified renderer
 * @param renderer
 */
void Rectangle::draw(SDL_Renderer* renderer) const
{
    const SDL_Color& fill { m_colour.fill };
    const SDL_Color& outline { m_colour.outline };

    if (fill.a != 0)
    {
        SDL_SetRenderDrawColor(renderer, fill.r, fill.g, fill.b, fill.a);
        SDL_RenderFillRect(renderer, &m_dimensions);
    }

    if (outline.a != 0)
    {
        SDL_SetRenderDrawColor(renderer, outline.r, outline.g, outline.b, outline.a);
        SDL_RenderRect(renderer, &m_dimensions);
    }
}

void Rectangle::drawRects(SDL_Renderer *renderer, const std::vector<Rectangle>& rects)
{
    for (const auto& rect : rects)
    {
        rect.draw(renderer);
    }
}
