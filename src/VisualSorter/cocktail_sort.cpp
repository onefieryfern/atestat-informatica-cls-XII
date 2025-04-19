#include "VisualSorter.h"
#include <utility>
#include <vector>

void VisualSorter::cocktail_sort_visual_stepped()
{
    // Set up variables
    auto& vector { m_state.sortVector };

    auto& start { m_state.sortingVars.at(0) };
    auto& end { m_state.sortingVars.at(1) };

    // Save current working indexes in a vector to be highlighted later
    std::vector<size_t> workingIndexes {};
    for (size_t i = start; i <= end; ++i) workingIndexes.push_back(i);

    // One forward sorting pass
    bool swapped { false };
    for (size_t i = start; i < end; ++i)
    {
        const size_t iNext { i + 1 };

        // Save initial state
        m_state.generatedSteps.push({ vector, { workingIndexes, { i, iNext }}, { m_barColours.auxiliary, m_barColours.selected } });

        if (int &current = vector.at(i), &next = vector.at(iNext); current > next)
        {
            std::swap(current, next);
            swapped = true;

            // Save new state
            m_state.generatedSteps.push({ vector, { workingIndexes, { i, iNext }}, { m_barColours.auxiliary, m_barColours.actedOn } });
        }
    }

    --end;
    workingIndexes.pop_back();

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
        m_state.generatedSteps.push({ vector, { workingIndexes, { i, iNext }}, { m_barColours.auxiliary, m_barColours.selected } });

        if (int &current = vector.at(i), &next = vector.at(iNext); current > next)
        {
            std::swap(current, next);
            swapped = true;

            // Save new state
            m_state.generatedSteps.push({ vector, { workingIndexes, { i, iNext }}, { m_barColours.auxiliary, m_barColours.actedOn } });
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
