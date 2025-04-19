#include "VisualSorter.h"
#include <utility>
#include <vector>

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
        m_state.generatedSteps.push({ vector, {{ iCurrent, iNext }}, { m_barColours.selected } });

        if (int &current = vector.at(iCurrent), &next = vector.at(iNext); current > next)
        {
            std::swap(current, next);

            // Save new state
            m_state.generatedSteps.push({ vector, {{ iCurrent, iNext }}, { m_barColours.actedOn } });
        }
    }

    // Prepare for next step or mark as done
    if (step + 1 < len - 1)
        ++step;
    else
        m_state.method = none;
}
