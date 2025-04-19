#ifndef ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H
#define ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H

#include "Rectangle.h"
#include "RenderWindow.h"
#include <array>
#include <queue>
#include <vector>

class VisualSorter
{
public:
    enum SortingMethod { none, selection, bubble, insertion, comb, cocktail, heap, quick, cycle };

    struct SortingStep
    {
        std::vector<int> sortVector {};
        std::vector<std::vector<size_t>> highlightIndexes {};
        std::vector<Rectangle::Colour> highlightColours {};
    };

    struct State
    {
        SortingMethod method { none };
        std::vector<int> sortVector {};
        std::vector<size_t> sortingVars {};
        std::queue<SortingStep> generatedSteps {};
    };

private:
    RenderWindow& m_renderWindow;
    State m_state;

    enum ColourIndex { rectDefault, selected, actedOn, auxiliary };
    std::array<Rectangle::Colour, 4> m_colours
    {
        Rectangle::Colour{ constants::colours::black, constants::colours::none },
        Rectangle::Colour{ constants::colours::blue, constants::colours::none },
        Rectangle::Colour{ constants::colours::red, constants::colours::none },
        Rectangle::Colour{ constants::colours::green, constants::colours::none }
    };

    bool continueSort();
    bool areRectsAvailable() const;

    void selection_sort_visual_stepped();
    void bubble_sort_visual_stepped();
    void insertion_sort_visual_stepped();
    void comb_sort_visual_stepped();
    void cocktail_sort_visual_stepped();
    void heapsort_visual_stepped();
    void quicksort_visual_stepped();
    void cycle_sort_visual_stepped();

public:
    VisualSorter
    (
        RenderWindow& renderWindow,
        Rectangle::Colour rectDefaultColour,
        Rectangle::Colour selectedColour,
        Rectangle::Colour actedOnColour,
        Rectangle::Colour auxiliaryColour
    );

    void startSort(const std::vector<int>& vector, SortingMethod method);
    bool hasSortFinished() const;
    std::vector<Rectangle> getCurrentStepRects();
};

#endif //ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H
