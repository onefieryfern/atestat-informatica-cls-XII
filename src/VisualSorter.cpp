#include "VisualSorter.h"
#include "graphing.h"
#include "utility.h"
#include <cmath>

VisualSorter::VisualSorter
    (
        RenderWindow& renderWindow,
        const Rectangle::Colours rectDefaultColour,
        const Rectangle::Colours selectedColour,
        const Rectangle::Colours actedOnColour,
        const Rectangle::Colours auxiliaryColour
    )
    : m_renderWindow { renderWindow }, m_colours { rectDefaultColour, selectedColour, actedOnColour, auxiliaryColour }
    {}

void VisualSorter::startSort(const std::vector<int>& vector, SortingMethod method)
{
    m_state = {};

    m_state.sortVector = vector;
    m_state.method = method;

    const size_t len { vector.size() };

    switch (m_state.method)
    {
    case selection:
        m_state.sortingVars.resize(1);
        m_state.sortingVars.at(0) = 0;
        break;
    case insertion:
        m_state.sortingVars.resize(1);
        m_state.sortingVars.at(0) = 1;
        break;
    case comb:
        m_state.sortingVars.resize(1);
        m_state.sortingVars.at(0) = len;
        break;
    case cocktail:
        m_state.sortingVars.resize(2);
        m_state.sortingVars.at(0) = 0;
        m_state.sortingVars.at(1) = len - 1;
        break;
    case heapsort:
        m_state.sortingVars.resize(2);
        m_state.sortingVars.at(0) = static_cast<size_t>(std::floor(len / 2));
        m_state.sortingVars.at(1) = len;
        break;
    case none:
    default:
        ;
    }

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
        case heapsort:
            heapsort_visual_stepped();
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

    std::vector currentStepRects { getRectsFromIntVector(m_renderWindow.getRenderer(), sortVector, m_colours.at(rectDefault)) };
    highlightRects(currentStepRects, highlightIndexes, highlightColours);

    m_state.generatedSteps.pop();

    return currentStepRects;
}

void VisualSorter::selection_sort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };
    const size_t len { vector.size() };

    auto& step { m_state.sortingVars.at(0) };

    // One sorting pass
    for (size_t j = step + 1; j < len; ++j)
    {
        const size_t iCurrent { step };
        const size_t iNext { j };

        // Save initial state
        m_state.generatedSteps.push({ vector, {{ iCurrent, iNext }}, { m_colours.at(selected) } });

        if (int &current = vector.at(iCurrent), &next = vector.at(iNext); current > next)
        {
            std::swap(current, next);

            // Save new state
            m_state.generatedSteps.push({ vector, {{ iCurrent, iNext }}, { m_colours.at(actedOn) } });
        }
    }

    // Prepare for next step or mark as done
    if (step + 1 < len - 1)
        ++step;
    else
        m_state.method = none;
}

void VisualSorter::bubble_sort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };
    const size_t len = vector.size();

    bool swapped = false;

    // One sorting pass
    for (size_t i = 0; i < len - 1; ++i)
    {
        const size_t iNext { i + 1 };

        // Save initial state
        m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_colours.at(selected) } });

        if (int &current = vector.at(i), &next = vector.at(iNext); current > next)
        {
            swapped = true;
            std::swap(current, next);

            // Save new state
            m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_colours.at(actedOn) } });
        }
    }

    // Mark if done
    if (!swapped)
        m_state.method = none;
}

void VisualSorter::insertion_sort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };
    const size_t len = vector.size();

    auto& step { m_state.sortingVars.at(0) };

    // One sorting pass
    for (size_t j = step; j > 0 && vector.at(j - 1) > vector.at(j); --j)
    {
        const size_t iNext { j - 1 };

        // Save initial state
        m_state.generatedSteps.push({ vector, {{ j, iNext }}, { m_colours.at(selected) } });

        std::swap(vector.at(j), vector.at(iNext));

        // Save new state
        m_state.generatedSteps.push({ vector, {{ j, iNext }}, { m_colours.at(actedOn) } });
    }

    // Prepare for next step or mark as done
    if (step + 1 < len)
        ++step;
    else
        m_state.method = none;
}

void VisualSorter::comb_sort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };
    const size_t len { vector.size() };

    size_t& gap { m_state.sortingVars.at(0) };
    constexpr double shrink { 1.3 };
    bool sorted { false };

    // Find the new gap
    gap = std::floor(static_cast<double>(gap) / shrink);
    if (gap <= 1)
    {
        gap = 1;
        sorted = true;
    }
    else if (gap == 9 || gap == 10)
    {
        gap = 11;
    }

    // One sorting pass
    for (size_t i = 0; i + gap < len; ++i)
    {
        const size_t iNext { i + gap };

        // Save initial state
        m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_colours.at(selected) } });

        if (int &current = vector.at(i), &next = vector.at(iNext); current > next)
        {
            std::swap(current, next);
            sorted = false;

            // Save new state
            m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_colours.at(actedOn) } });
        }
    }

    // Mark if done
    if (sorted)
        m_state.method = none;
}

void VisualSorter::cocktail_sort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };

    auto& start { m_state.sortingVars.at(0) };
    auto& end { m_state.sortingVars.at(1) };

    // One forward sorting pass
    bool swapped { false };
    for (size_t i = start; i < end; ++i)
    {
        const size_t iNext { i + 1 };

        // Save initial state
        m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_colours.at(selected) } });

        if (int &current = vector.at(i), &next = vector.at(iNext); current > next)
        {
            std::swap(current, next);
            swapped = true;

            // Save new state
            m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_colours.at(actedOn) } });
        }
    }

    --end;

    // Mark if done (early)
    if (!swapped)
    {
        m_state.method = none;
        return;
    }

    // One backward sorting pass
    swapped = false;
    for (size_t i = end - 1; i >= start; --i)
    {
        const size_t iNext { i + 1 };

        // Save initial state
        m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_colours.at(selected) } });

        if (int &current = vector.at(i), &next = vector.at(iNext); current > next)
        {
            std::swap(current, next);
            swapped = true;

            // Save new state
            m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_colours.at(actedOn) } });
        }

        // Start might be equal to 0 but cannot use i >= 0 as condition with size_t
        if (i == 0)
            break;
    }

    ++start;

    // Mark if done
    if (!swapped)
        m_state.method = none;
}

void VisualSorter::heapsort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };

    auto& start { m_state.sortingVars.at(0) };
    auto& end { m_state.sortingVars.at(1) };

    if (end > 1)
    {
        if (start > 0)
            --start;
        else
        {
            --end;

            // Save initial state
            m_state.generatedSteps.push({ vector, {{ 0, end }}, { m_colours.at(selected) } });

            std::swap(vector.at(0), vector.at(end));

            // Save new state
            m_state.generatedSteps.push({ vector, {{ 0, end }}, { m_colours.at(actedOn) } });
        }

        for (size_t root { start }; 2 * root + 1 < end; )
        {
            size_t child { 2 * root + 1 };

            // Save current heap indexes in a vector to be highlighted later
            std::vector<size_t> heapIndexes {};
            for (size_t i = start; i < end; ++i) heapIndexes.push_back(i);

            // Save initial state
            m_state.generatedSteps.push({ vector, { heapIndexes, { root, child } }, { m_colours.at(auxiliary), m_colours.at(selected) } });

            if (child + 1 < end && vector.at(child) < vector.at(child + 1))
                ++child;

            // Save new initial state
            m_state.generatedSteps.push({ vector, { heapIndexes, { root, child } }, { m_colours.at(auxiliary), m_colours.at(selected) } });

            if (vector.at(root) < vector.at(child))
            {
                std::swap(vector.at(root), vector.at(child));

                // Save new state
                m_state.generatedSteps.push({ vector, { heapIndexes, { root, child } }, { m_colours.at(auxiliary), m_colours.at(actedOn) } });

                root = child;
            }
            else
                break;
        }
    }

    // Mark if done
    if (end <= 1)
        m_state.method = none;
}
