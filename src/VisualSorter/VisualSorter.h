#ifndef ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H
#define ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H

#include "Rectangle.h"
#include "RenderWindow.h"
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

    struct BarColours
    {
        Rectangle::Colour main { constants::colours::black, constants::colours::none };
        Rectangle::Colour selected { constants::colours::blue, constants::colours::none };
        Rectangle::Colour actedOn { constants::colours::red, constants::colours::none };
        Rectangle::Colour auxiliary { constants::colours::green, constants::colours::none };
    };

private:
    RenderWindow& m_renderWindow;
    State m_state;
    BarColours m_barColours {};

    bool continueSort();
    [[nodiscard]] bool areRectsAvailable() const;

    void selection_sort_visual_stepped();
    void bubble_sort_visual_stepped();
    void insertion_sort_visual_stepped();
    void comb_sort_visual_stepped();
    void cocktail_sort_visual_stepped();
    void heapsort_visual_stepped();
    void quicksort_visual_stepped();
    void cycle_sort_visual_stepped();

public:
    explicit VisualSorter(RenderWindow& renderWindow, const BarColours& barColours);

    void startSort(const std::vector<int>& vector, SortingMethod method);
    [[nodiscard]] bool hasSortFinished() const;
    std::vector<Rectangle> getCurrentStepRects();
};

#endif //ATESTAT_INFORMATICA_CLS_XII_VISUALSORTER_H
