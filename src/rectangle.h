#ifndef ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H
#define ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H

#include <SDL3/SDL.h>
#include <vector>

class Rectangle
{
public:
    struct Colours
    {
        SDL_Color fill = {0, 0, 0, 0};
        SDL_Color outline = {0, 0, 0, 0};
    };
private:
    SDL_FRect m_dimensions {0, 0, 0, 0};
    SDL_Color m_fillColour {0, 0, 0, 0};
    SDL_Color m_outlineColour {0, 0, 0, 0};
public:
    Rectangle(SDL_FRect sdlFRect, SDL_Color fillColour, SDL_Color outlineColour);
    Rectangle(SDL_FRect sdlFRect, Colours colours);

    SDL_FRect getDimensions() const;
    SDL_Color getFillColour() const;
    SDL_Color getOutlineColour() const;
    Colours getColours() const;

    void setDimensions(SDL_FRect sdlFRect);
    void setFillColour(SDL_Color colour);
    void setOutlineColour(SDL_Color colour);
    void setColours(Colours colours);

    void draw(SDL_Renderer* renderer) const;
    static void drawRects(SDL_Renderer* renderer, const std::vector<Rectangle>& rects);
};

#endif //ATESTAT_INFORMATICA_CLS_XII_RECTANGLE_H
