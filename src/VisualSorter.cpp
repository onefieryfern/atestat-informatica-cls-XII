#include "VisualSorter.h"
#include "graphing.h"

VisualSorter::VisualSorter(RenderWindow& renderWindow, Properties properties)
    : m_renderWindow { renderWindow }
{
    m_properties = properties;
}

void VisualSorter::startSort(const std::vector<int>& vector, SortingMethod method)
{
    m_state.sortVector = vector;
    m_state.method = method;

    switch (m_state.method)
    {
    case selection:
        m_state.nextStep = 0;
        break;
    case insertion:
        m_state.nextStep = 1;
        break;
    case none:
    default:
        m_state.nextStep = 0;
    }

    // Clean up remaining data from the previous sort
    m_state.generatedSteps.clear();

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
            selection_sort_visual_stepped(m_state.nextStep);
            break;
        case bubble:
            bubble_sort_visual_stepped();
            break;
        case insertion:
            insertion_sort_visual_stepped(m_state.nextStep);
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

std::vector<Rectangle> VisualSorter::getNextStepRects()
{
    if (!areRectsAvailable())
        if (!continueSort())
            return {};

    SortingStep& firstInQueue { m_state.generatedSteps.at(0) };
    std::vector<Rectangle> generatedSteps =
        getRectsFromIntVector(m_renderWindow.getRenderer(), firstInQueue.sortVector, m_properties.rectColour);
    for (const auto highlightedIndex : firstInQueue.highlightIndexes)
    {
        generatedSteps.at(highlightedIndex).setColours(firstInQueue.highlightColour);
    }

    m_state.generatedSteps.erase(m_state.generatedSteps.begin());
    return generatedSteps;
}

void VisualSorter::selection_sort_visual_stepped(const size_t step)
{
    auto& vector { m_state.sortVector };
    const size_t len = vector.size();

    for (size_t j = step + 1; j < len; ++j)
    {
        // Save initial state
        m_state.generatedSteps.push_back({ vector, { step, j }, m_properties.selectedColour });

        int& current { vector.at(step) };
        int& next { vector.at(j) };

        if (current > next)
        {
            std::swap(current, next);

            // Save new state
            m_state.generatedSteps.push_back({ vector, { step, j }, m_properties.swappedColour });
        }
    }

    if (step + 1 < len - 1)
        m_state.nextStep = step + 1;
    else
        m_state.method = none;
}

void VisualSorter::bubble_sort_visual_stepped()
{
    auto& vector { m_state.sortVector };
    const size_t len = vector.size();

    bool swapped = false;

    for (size_t i = 0; i < len - 1; ++i)
    {
        // Save initial state
        m_state.generatedSteps.push_back({ vector, { i, i + 1 }, m_properties.selectedColour });

        int& current { vector.at(i) };
        int& next { vector.at(i + 1) };

        if (current > next)
        {
            swapped = true;
            std::swap(current, next);

            // Save new state
            m_state.generatedSteps.push_back({ vector, { i, i + 1 }, m_properties.swappedColour });
        }
    }

    if (!swapped)
        m_state.method = none;
}

void VisualSorter::insertion_sort_visual_stepped(const size_t step)
{
    auto& vector { m_state.sortVector };
    const size_t len = vector.size();

    for (size_t j = step; j > 0 && vector.at(j - 1) > vector.at(j); --j)
    {
        // Save initial state
        m_state.generatedSteps.push_back({ vector, { j, j - 1 }, m_properties.selectedColour });

        std::swap(vector.at(j), vector.at(j - 1));

        // Save new state
        m_state.generatedSteps.push_back({ vector, { j, j - 1 }, m_properties.swappedColour });
    }

    if (step + 1 < len)
        m_state.nextStep = step + 1;
    else
        m_state.method = none;
}
