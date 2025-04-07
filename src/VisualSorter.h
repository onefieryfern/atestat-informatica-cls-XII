#ifndef ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H
#define ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H

#include "rectangle.h"
#include "render.h"
#include <array>
#include <queue>
#include <vector>

class VisualSorter
{
public:
    enum SortingMethod { none, selection, bubble, insertion, comb, cocktail, heapsort, quicksort };

    struct SortingStep
    {
        std::vector<int> sortVector {};
        std::vector<std::vector<size_t>> highlightIndexes {};
        std::vector<Rectangle::Colours> highlightColours {};
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
    std::array<Rectangle::Colours, 4> m_colours
    {
        Rectangle::Colours{ constants::colours::black, constants::colours::none },
        Rectangle::Colours{ constants::colours::blue, constants::colours::none },
        Rectangle::Colours{ constants::colours::red, constants::colours::none },
        Rectangle::Colours{ constants::colours::green, constants::colours::none }
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

public:
    VisualSorter
    (
        RenderWindow& renderWindow,
        Rectangle::Colours rectDefaultColour,
        Rectangle::Colours selectedColour,
        Rectangle::Colours actedOnColour,
        Rectangle::Colours auxiliaryColour
    );

    void startSort(const std::vector<int>& vector, SortingMethod method);
    bool hasSortFinished() const;
    std::vector<Rectangle> getCurrentStepRects();
};

#endif //ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H
