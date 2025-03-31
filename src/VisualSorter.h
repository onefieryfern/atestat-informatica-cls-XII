#ifndef ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H
#define ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H

#include "rectangle.h"
#include "render.h"
#include <SDL3/SDL.h>
#include <vector>

class VisualSorter
{
public:
    enum SortingMethod { none, selection, bubble, insertion, comb };

    struct Properties
    {
        SDL_Color backgroundColour { constants::colours::white };
        Rectangle::Colours rectColour { constants::colours::black, constants::colours::none };
        Rectangle::Colours selectedColour { constants::colours::blue, constants::colours::none };
        Rectangle::Colours swappedColour { constants::colours::red, constants::colours::none };
    };

    struct SortingStep
    {
        std::vector<int> sortVector {};
        std::vector<size_t> highlightIndexes {};
        Rectangle::Colours highlightColour {};
    };

    struct State
    {
        SortingMethod method { none };
        std::vector<int> sortVector {};
        std::vector<SortingStep> generatedSteps {};
        std::vector<size_t> sortingVars {};
        size_t nextStep {};
    };

private:
    RenderWindow& m_renderWindow;
    Properties m_properties;
    State m_state;

    bool continueSort();
    bool areRectsAvailable() const;
    void cleanBeforeSort();

    void selection_sort_visual_stepped(size_t step);
    void bubble_sort_visual_stepped();
    void insertion_sort_visual_stepped(size_t step);
    void comb_sort_visual_stepped();

public:
    VisualSorter(RenderWindow& renderWindow, Properties properties);

    void startSort(const std::vector<int>& vector, SortingMethod method);
    bool hasSortFinished() const;
    std::vector<Rectangle> getNextStepRects();
};

#endif //ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H
