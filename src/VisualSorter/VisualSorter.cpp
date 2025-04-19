#include "VisualSorter.h"
#include "chart.h"
#include "utility.h"
#include <cmath>

VisualSorter::VisualSorter(RenderWindow& renderWindow, const BarColours& barColours)
    : m_renderWindow { renderWindow }, m_barColours { barColours }
    {}

void VisualSorter::startSort(const std::vector<int>& vector, const SortingMethod method)
{
    // Clear any leftover data
    m_state = {};

    // Set internal state
    m_state.sortVector = vector;
    m_state.method = method;

    // Set algorithm-specific internal state
    const size_t len { vector.size() };
    auto& sortingVars { m_state.sortingVars };

    switch (m_state.method)
    {
    case selection:
        sortingVars.resize(1);
        sortingVars.at(0) = 0;
        break;
    case insertion:
        sortingVars.resize(1);
        sortingVars.at(0) = 1;
        break;
    case comb:
        sortingVars.resize(1);
        sortingVars.at(0) = len;
        break;
    case cocktail:
        sortingVars.resize(2);
        sortingVars.at(0) = 0;
        sortingVars.at(1) = len - 1;
        break;
    case heap:
        sortingVars.resize(2);
        sortingVars.at(0) = static_cast<size_t>(std::floor(len / 2));
        sortingVars.at(1) = len;
        break;
    case quick:
        sortingVars.resize(2);
        sortingVars.at(0) = len - 1; // hi
        sortingVars.at(1) = 0; // lo
        break;
    case cycle:
        sortingVars.resize(1);
        sortingVars.at(0) = 0;
        break;
    case none:
    default:
        ;
    }

    // Start sorting
    continueSort();
}

/**
 * Continues sorting, if it was started previously and it has not finished
 * @return true if sorting has continued successfully and false otherwise
 */
bool VisualSorter::continueSort()
{
    while (!areRectsAvailable())
    {
        switch (m_state.method)
        {
        case selection:
            selection_sort_visual_stepped();
            break;
        case bubble:
            bubble_sort_visual_stepped();
            break;
        case insertion:
            insertion_sort_visual_stepped();
            break;
        case comb:
            comb_sort_visual_stepped();
            break;
        case cocktail:
            cocktail_sort_visual_stepped();
            break;
        case heap:
            heapsort_visual_stepped();
            break;
        case quick:
            quicksort_visual_stepped();
            break;
        case cycle:
            cycle_sort_visual_stepped();
            break;
        case none:
        default:
            return false;
        }
    }

    return true;
}

bool VisualSorter::hasSortFinished() const
{
    return m_state.method == none && !areRectsAvailable();
}

bool VisualSorter::areRectsAvailable() const
{
    return !m_state.generatedSteps.empty();
}

std::vector<Rectangle> VisualSorter::getCurrentStepRects()
{
    if (!areRectsAvailable())
        if (!continueSort())
            // Preferably, this should never be reached
            return {};

    auto& [sortVector, highlightIndexes, highlightColours] { m_state.generatedSteps.front() };

    std::vector currentStepRects
        { chart::makeBarChartRects(m_renderWindow.getRenderer(), sortVector, m_barColours.main) };
    highlightRects(currentStepRects, highlightIndexes, highlightColours);

    m_state.generatedSteps.pop();

    return currentStepRects;
}
