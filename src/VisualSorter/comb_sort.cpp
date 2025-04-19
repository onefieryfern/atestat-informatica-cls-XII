#include "VisualSorter.h"
#include <cmath>
#include <utility>
#include <vector>

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
        m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_barColours.selected } });

        if (int &current = vector.at(i), &next = vector.at(iNext); current > next)
        {
            std::swap(current, next);
            sorted = false;

            // Save new state
            m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_barColours.actedOn } });
        }
    }

    // Mark if done
    if (sorted)
        m_state.method = none;
}
