#include "VisualSorter.h"
#include <utility>
#include <vector>

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
        m_state.generatedSteps.push({ vector, { { step }, { j, iNext } }, { m_barColours.auxiliary, m_barColours.selected } });

        std::swap(vector.at(j), vector.at(iNext));

        // Save new state
        m_state.generatedSteps.push({ vector, { { step }, { j, iNext } }, { m_barColours.auxiliary, m_barColours.actedOn } });
    }

    // Prepare for next step or mark as done
    if (step + 1 < len)
        ++step;
    else
        m_state.method = none;
}
