#include "VisualSorter.h"
#include <utility>
#include <vector>

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
        m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_barColours.selected } });

        if (int &current = vector.at(i), &next = vector.at(iNext); current > next)
        {
            swapped = true;
            std::swap(current, next);

            // Save new state
            m_state.generatedSteps.push({ vector, {{ i, iNext }}, { m_barColours.actedOn } });
        }
    }

    // Mark if done
    if (!swapped)
        m_state.method = none;
}
