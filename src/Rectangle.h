#ifndef ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H
#define ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H

#include "constants.h"
#include <SDL3/SDL.h>
#include <vector>

class Rectangle
{
public:
    struct Colour
    {
        SDL_Color fill { constants::colours::none };
        SDL_Color outline { constants::colours::none };
    };
private:
    SDL_FRect m_dimensions { 0, 0, 0, 0 };
    Colour m_colour { constants::colours::none, constants::colours::none };
public:
    explicit Rectangle(SDL_FRect rect, Colour colour = { constants::colours::none, constants::colours::none });

    [[nodiscard]] SDL_FRect getDimensions() const;
    [[nodiscard]] Colour getColour() const;

    void setDimensions(SDL_FRect sdlFRect);
    void setColour(Colour colour);

    void draw(SDL_Renderer* renderer) const;
    static void drawRects(SDL_Renderer* renderer, const std::vector<Rectangle>& rects);
};

#endif //ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H
